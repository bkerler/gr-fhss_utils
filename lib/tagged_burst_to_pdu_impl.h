/* -*- c++ -*- */
/*
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_FHSS_UTILS_TAGGED_BURST_TO_PDU_IMPL_H
#define INCLUDED_FHSS_UTILS_TAGGED_BURST_TO_PDU_IMPL_H

#include <fhss_utils/tagged_burst_to_pdu.h>
#include <queue>
#include <boost/lockfree/queue.hpp>
#include <gnuradio/blocks/rotator.h>
#include <gnuradio/filter/fir_filter.h>

namespace gr {
  namespace fhss_utils {

    struct burst_data {
        uint64_t id;
        uint64_t offset;
        uint64_t data_skip;
        float magnitude;
        float relative_frequency;
        float center_frequency;
        float sample_rate;
        size_t len;
        size_t rot_skip;
        pmt::pmt_t dict;
        gr_complex * data;
        gr_complex* rot_tmp;
        blocks::rotator rotate;
    };

    struct two_gr_complex {
        two_gr_complex() {}
        two_gr_complex(gr_complex* a, gr_complex* b) : one(a), two(b) {}
        gr_complex* one;
        gr_complex* two;
    };

    struct buffer {
        buffer(size_t capacity=0) {
          reset();
          if (capacity > 0)
            data.resize(int(capacity*1.1));
          data.resize(0);
          desired_max = capacity;
        }
        std::vector<tag_t> new_burst_tags;
        std::vector<tag_t> rx_time_tags;
        std::vector<tag_t> gone_burst_tags;
        std::vector<gr_complex> data;
        size_t desired_max;
        bool end_flag;
        size_t start;

        bool is_full() {
          return data.size() >= desired_max;
        }

        void reset() {
          new_burst_tags.resize(0);
          rx_time_tags.resize(0);
          gone_burst_tags.resize(0);
          data.resize(0);
          end_flag = false;
        }

        void add_data(const gr_complex* d, size_t length) {
          //size_t clength = std::min(length, data.capacity() - data.size());
          //printf("Going to add %zu data of %zu, cap = %zu, size = %zu, ptr = %p\n", clength, length, data.capacity(), data.size(), this);
          data.insert(data.end(), d, d + length);
        }

        void add_tags(const std::vector<tag_t>& new_b, const std::vector<tag_t>& rx_time, const std::vector<tag_t> gone_b) {
          new_burst_tags.insert(new_burst_tags.end(), new_b.begin(), new_b.end());
          rx_time_tags.insert(rx_time_tags.end(), rx_time.begin(), rx_time.end());
          gone_burst_tags.insert(gone_burst_tags.end(), gone_b.begin(), gone_b.end());
        }
    };

    class tagged_burst_to_pdu_impl : public tagged_burst_to_pdu
    {
     private:
       bool d_debug;
       float d_relative_center_frequency;
       float d_relative_span;
       float d_relative_sample_rate;
       float d_sample_rate;
       int d_min_burst_size;
       int d_max_burst_size;
       int d_outstanding;
       int d_max_outstanding;
       uint64_t d_n_dropped_bursts;
       size_t d_block_increment;
       bool d_blocked;
       size_t d_max_id;
       int d_num_threads;

       buffer* d_current_buffer;

       tag_t d_current_rx_time_tag;
       std::queue<tag_t> d_rx_time_tags;
       std::queue<two_gr_complex> d_alloced_arrays;
       std::vector<float> d_taps;
       size_t d_decimation;
       std::vector<filter::kernel::fir_filter_ccf*> d_input_fir_filters;

       boost::lockfree::queue<buffer*> d_write_queue;
       boost::lockfree::queue<buffer*> d_work_queue;
       boost::thread* process_thread;

       float d_lower_border;
       float d_upper_border;

       std::map<uint64_t, burst_data> d_bursts;
       std::map<uint64_t, burst_data> d_new_bursts;

       void append_to_burst(burst_data &burst, const gr_complex * data, size_t n);
       void publish_burst(burst_data &burst);

       void create_new_bursts(const buffer& work_buffer);
       void publish_and_remove_old_bursts(const buffer& work_buffer);
       void update_current_bursts(int noutput_items, const gr_complex * in);
       void process_data();

       int get_output_queue_size();
       int get_output_max_queue_size();
       void burst_handled(pmt::pmt_t msg);

       double convert_rx_time(const tag_t &rx_time_tag);

       const pmt::pmt_t NEW_BURST_TAG = pmt::mp("new_burst");
       const pmt::pmt_t GONE_BURST_TAG = pmt::mp("gone_burst");
       const pmt::pmt_t RX_TIME_TAG = pmt::mp("rx_time");
       const pmt::pmt_t META_RELATIVE_FREQ = pmt::mp("relative_frequency");
       const pmt::pmt_t META_ID = pmt::mp("burst_id");
       const pmt::pmt_t META_MAGNITUDE = pmt::mp("magnitude");
       const pmt::pmt_t META_CENTER_FREQ = pmt::mp("center_frequency");
       const pmt::pmt_t META_SAMP_RATE = pmt::mp("sample_rate");
       const pmt::pmt_t META_START_TIME = pmt::mp("start_time");
       const pmt::pmt_t META_DURATION = pmt::mp("duration");
       const pmt::pmt_t META_START_OFFSET = pmt::mp("start_offset");
       const pmt::pmt_t META_END_OFFSET = pmt::mp("end_offset");

       const pmt::pmt_t PDU_OUT_PORT = pmt::mp("cpdus");

       // The gnuradio filter function reads memory that it shouldn't.  We offset our array by this amount to
       // prevent bad things from happening.  If we fix the filter function, then we can get rid of this.
       const size_t ROT_TMP_OFFSET = 4;

     public:
      static const size_t d_block_size = 32*1024;
      tagged_burst_to_pdu_impl(size_t decimation, const std::vector<float>& taps, float min_burst_time, float max_burst_time,
          float relative_center_frequency, float relative_span, float relative_sample_rate, float sample_rate, int num_threads);
      ~tagged_burst_to_pdu_impl();

      bool stop();

      /*uint64_t get_n_dropped_bursts();*/

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace fhss_utils
} // namespace gr

#endif /* INCLUDED_FHSS_UTILS_TAGGED_BURST_TO_PDU_IMPL_H */

