/*
 * Copyright 2021 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(constants.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(2973a4c06038ea400d28a5f8f8f9087e)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/fhss_utils/constants.h>
// pydoc.h is automatically generated in the build directory
#include <constants_pydoc.h>

void bind_constants(py::module& m)
{


    m.def("PMTCONSTSTR__in", &::gr::fhss_utils::PMTCONSTSTR__in, D(PMTCONSTSTR__in));


    m.def("PMTCONSTSTR__out", &::gr::fhss_utils::PMTCONSTSTR__out, D(PMTCONSTSTR__out));


    m.def("PMTCONSTSTR__center_frequency",
          &::gr::fhss_utils::PMTCONSTSTR__center_frequency,
          D(PMTCONSTSTR__center_frequency));


    m.def("PMTCONSTSTR__relative_frequency",
          &::gr::fhss_utils::PMTCONSTSTR__relative_frequency,
          D(PMTCONSTSTR__relative_frequency));


    m.def("PMTCONSTSTR__sample_rate",
          &::gr::fhss_utils::PMTCONSTSTR__sample_rate,
          D(PMTCONSTSTR__sample_rate));


    m.def("PMTCONSTSTR__bandwidth",
          &::gr::fhss_utils::PMTCONSTSTR__bandwidth,
          D(PMTCONSTSTR__bandwidth));


    m.def("PMTCONSTSTR__pwr_db",
          &::gr::fhss_utils::PMTCONSTSTR__pwr_db,
          D(PMTCONSTSTR__pwr_db));


    m.def("PMTCONSTSTR__snr_db",
          &::gr::fhss_utils::PMTCONSTSTR__snr_db,
          D(PMTCONSTSTR__snr_db));


    m.def("PMTCONSTSTR__debug",
          &::gr::fhss_utils::PMTCONSTSTR__debug,
          D(PMTCONSTSTR__debug));


    m.def("PMTCONSTSTR__rx_freq",
          &::gr::fhss_utils::PMTCONSTSTR__rx_freq,
          D(PMTCONSTSTR__rx_freq));


    m.def("PMTCONSTSTR__burst_id",
          &::gr::fhss_utils::PMTCONSTSTR__burst_id,
          D(PMTCONSTSTR__burst_id));


    m.def("PMTCONSTSTR__magnitude",
          &::gr::fhss_utils::PMTCONSTSTR__magnitude,
          D(PMTCONSTSTR__magnitude));


    m.def("PMTCONSTSTR__noise_density",
          &::gr::fhss_utils::PMTCONSTSTR__noise_density,
          D(PMTCONSTSTR__noise_density));


    m.def("PMTCONSTSTR__new_burst",
          &::gr::fhss_utils::PMTCONSTSTR__new_burst,
          D(PMTCONSTSTR__new_burst));


    m.def("PMTCONSTSTR__gone_burst",
          &::gr::fhss_utils::PMTCONSTSTR__gone_burst,
          D(PMTCONSTSTR__gone_burst));


    m.def("PMTCONSTSTR__rx_time",
          &::gr::fhss_utils::PMTCONSTSTR__rx_time,
          D(PMTCONSTSTR__rx_time));


    m.def("PMTCONSTSTR__start_time",
          &::gr::fhss_utils::PMTCONSTSTR__start_time,
          D(PMTCONSTSTR__start_time));


    m.def("PMTCONSTSTR__duration",
          &::gr::fhss_utils::PMTCONSTSTR__duration,
          D(PMTCONSTSTR__duration));


    m.def("PMTCONSTSTR__cpdus",
          &::gr::fhss_utils::PMTCONSTSTR__cpdus,
          D(PMTCONSTSTR__cpdus));


    m.def("PMTCONSTSTR__start_offset",
          &::gr::fhss_utils::PMTCONSTSTR__start_offset,
          D(PMTCONSTSTR__start_offset));


    m.def("PMTCONSTSTR__end_offset",
          &::gr::fhss_utils::PMTCONSTSTR__end_offset,
          D(PMTCONSTSTR__end_offset));


    m.def("PMTCONSTSTR__input_rate",
          &::gr::fhss_utils::PMTCONSTSTR__input_rate,
          D(PMTCONSTSTR__input_rate));


    m.def("PMTCONSTSTR__cut_short",
          &::gr::fhss_utils::PMTCONSTSTR__cut_short,
          D(PMTCONSTSTR__cut_short));
}
