/* -*- c++ -*- */
/* 
 * Copyright 2018 Ahmet Inan, Ron Economos.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ldpc_decoder_cb_impl.h"
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <algorithm>

#define FACTOR 2

constexpr int DVB_S2_TABLE_B1::DEG[];
constexpr int DVB_S2_TABLE_B1::LEN[];
constexpr int DVB_S2_TABLE_B1::POS[];

constexpr int DVB_S2_TABLE_B2::DEG[];
constexpr int DVB_S2_TABLE_B2::LEN[];
constexpr int DVB_S2_TABLE_B2::POS[];

constexpr int DVB_S2_TABLE_B3::DEG[];
constexpr int DVB_S2_TABLE_B3::LEN[];
constexpr int DVB_S2_TABLE_B3::POS[];

constexpr int DVB_S2_TABLE_B4::DEG[];
constexpr int DVB_S2_TABLE_B4::LEN[];
constexpr int DVB_S2_TABLE_B4::POS[];

constexpr int DVB_S2_TABLE_B5::DEG[];
constexpr int DVB_S2_TABLE_B5::LEN[];
constexpr int DVB_S2_TABLE_B5::POS[];

constexpr int DVB_S2_TABLE_B6::DEG[];
constexpr int DVB_S2_TABLE_B6::LEN[];
constexpr int DVB_S2_TABLE_B6::POS[];

constexpr int DVB_S2_TABLE_B7::DEG[];
constexpr int DVB_S2_TABLE_B7::LEN[];
constexpr int DVB_S2_TABLE_B7::POS[];

constexpr int DVB_S2_TABLE_B8::DEG[];
constexpr int DVB_S2_TABLE_B8::LEN[];
constexpr int DVB_S2_TABLE_B8::POS[];

constexpr int DVB_S2_TABLE_B9::DEG[];
constexpr int DVB_S2_TABLE_B9::LEN[];
constexpr int DVB_S2_TABLE_B9::POS[];

constexpr int DVB_S2_TABLE_B10::DEG[];
constexpr int DVB_S2_TABLE_B10::LEN[];
constexpr int DVB_S2_TABLE_B10::POS[];

constexpr int DVB_S2_TABLE_B11::DEG[];
constexpr int DVB_S2_TABLE_B11::LEN[];
constexpr int DVB_S2_TABLE_B11::POS[];

constexpr int DVB_S2X_TABLE_B1::DEG[];
constexpr int DVB_S2X_TABLE_B1::LEN[];
constexpr int DVB_S2X_TABLE_B1::POS[];

constexpr int DVB_S2X_TABLE_B2::DEG[];
constexpr int DVB_S2X_TABLE_B2::LEN[];
constexpr int DVB_S2X_TABLE_B2::POS[];

constexpr int DVB_S2X_TABLE_B3::DEG[];
constexpr int DVB_S2X_TABLE_B3::LEN[];
constexpr int DVB_S2X_TABLE_B3::POS[];

constexpr int DVB_S2X_TABLE_B4::DEG[];
constexpr int DVB_S2X_TABLE_B4::LEN[];
constexpr int DVB_S2X_TABLE_B4::POS[];

constexpr int DVB_S2X_TABLE_B5::DEG[];
constexpr int DVB_S2X_TABLE_B5::LEN[];
constexpr int DVB_S2X_TABLE_B5::POS[];

constexpr int DVB_S2X_TABLE_B6::DEG[];
constexpr int DVB_S2X_TABLE_B6::LEN[];
constexpr int DVB_S2X_TABLE_B6::POS[];

constexpr int DVB_S2X_TABLE_B7::DEG[];
constexpr int DVB_S2X_TABLE_B7::LEN[];
constexpr int DVB_S2X_TABLE_B7::POS[];

constexpr int DVB_S2X_TABLE_B8::DEG[];
constexpr int DVB_S2X_TABLE_B8::LEN[];
constexpr int DVB_S2X_TABLE_B8::POS[];

constexpr int DVB_S2X_TABLE_B9::DEG[];
constexpr int DVB_S2X_TABLE_B9::LEN[];
constexpr int DVB_S2X_TABLE_B9::POS[];

constexpr int DVB_S2X_TABLE_B10::DEG[];
constexpr int DVB_S2X_TABLE_B10::LEN[];
constexpr int DVB_S2X_TABLE_B10::POS[];

constexpr int DVB_S2X_TABLE_B11::DEG[];
constexpr int DVB_S2X_TABLE_B11::LEN[];
constexpr int DVB_S2X_TABLE_B11::POS[];

constexpr int DVB_S2X_TABLE_B12::DEG[];
constexpr int DVB_S2X_TABLE_B12::LEN[];
constexpr int DVB_S2X_TABLE_B12::POS[];

constexpr int DVB_S2X_TABLE_B13::DEG[];
constexpr int DVB_S2X_TABLE_B13::LEN[];
constexpr int DVB_S2X_TABLE_B13::POS[];

constexpr int DVB_S2X_TABLE_B14::DEG[];
constexpr int DVB_S2X_TABLE_B14::LEN[];
constexpr int DVB_S2X_TABLE_B14::POS[];

constexpr int DVB_S2X_TABLE_B15::DEG[];
constexpr int DVB_S2X_TABLE_B15::LEN[];
constexpr int DVB_S2X_TABLE_B15::POS[];

constexpr int DVB_S2X_TABLE_B16::DEG[];
constexpr int DVB_S2X_TABLE_B16::LEN[];
constexpr int DVB_S2X_TABLE_B16::POS[];

constexpr int DVB_S2X_TABLE_B17::DEG[];
constexpr int DVB_S2X_TABLE_B17::LEN[];
constexpr int DVB_S2X_TABLE_B17::POS[];

constexpr int DVB_S2X_TABLE_B18::DEG[];
constexpr int DVB_S2X_TABLE_B18::LEN[];
constexpr int DVB_S2X_TABLE_B18::POS[];

constexpr int DVB_S2X_TABLE_B19::DEG[];
constexpr int DVB_S2X_TABLE_B19::LEN[];
constexpr int DVB_S2X_TABLE_B19::POS[];

constexpr int DVB_S2X_TABLE_B20::DEG[];
constexpr int DVB_S2X_TABLE_B20::LEN[];
constexpr int DVB_S2X_TABLE_B20::POS[];

constexpr int DVB_S2X_TABLE_B21::DEG[];
constexpr int DVB_S2X_TABLE_B21::LEN[];
constexpr int DVB_S2X_TABLE_B21::POS[];

constexpr int DVB_S2X_TABLE_B22::DEG[];
constexpr int DVB_S2X_TABLE_B22::LEN[];
constexpr int DVB_S2X_TABLE_B22::POS[];

constexpr int DVB_S2X_TABLE_B23::DEG[];
constexpr int DVB_S2X_TABLE_B23::LEN[];
constexpr int DVB_S2X_TABLE_B23::POS[];

constexpr int DVB_S2X_TABLE_B24::DEG[];
constexpr int DVB_S2X_TABLE_B24::LEN[];
constexpr int DVB_S2X_TABLE_B24::POS[];

constexpr int DVB_S2_TABLE_C1::DEG[];
constexpr int DVB_S2_TABLE_C1::LEN[];
constexpr int DVB_S2_TABLE_C1::POS[];

constexpr int DVB_S2_TABLE_C2::DEG[];
constexpr int DVB_S2_TABLE_C2::LEN[];
constexpr int DVB_S2_TABLE_C2::POS[];

constexpr int DVB_S2_TABLE_C3::DEG[];
constexpr int DVB_S2_TABLE_C3::LEN[];
constexpr int DVB_S2_TABLE_C3::POS[];

constexpr int DVB_S2_TABLE_C4::DEG[];
constexpr int DVB_S2_TABLE_C4::LEN[];
constexpr int DVB_S2_TABLE_C4::POS[];

constexpr int DVB_S2_TABLE_C5::DEG[];
constexpr int DVB_S2_TABLE_C5::LEN[];
constexpr int DVB_S2_TABLE_C5::POS[];

constexpr int DVB_S2_TABLE_C6::DEG[];
constexpr int DVB_S2_TABLE_C6::LEN[];
constexpr int DVB_S2_TABLE_C6::POS[];

constexpr int DVB_S2_TABLE_C7::DEG[];
constexpr int DVB_S2_TABLE_C7::LEN[];
constexpr int DVB_S2_TABLE_C7::POS[];

constexpr int DVB_S2_TABLE_C8::DEG[];
constexpr int DVB_S2_TABLE_C8::LEN[];
constexpr int DVB_S2_TABLE_C8::POS[];

constexpr int DVB_S2_TABLE_C9::DEG[];
constexpr int DVB_S2_TABLE_C9::LEN[];
constexpr int DVB_S2_TABLE_C9::POS[];

constexpr int DVB_S2_TABLE_C10::DEG[];
constexpr int DVB_S2_TABLE_C10::LEN[];
constexpr int DVB_S2_TABLE_C10::POS[];

constexpr int DVB_S2X_TABLE_C1::DEG[];
constexpr int DVB_S2X_TABLE_C1::LEN[];
constexpr int DVB_S2X_TABLE_C1::POS[];

constexpr int DVB_S2X_TABLE_C2::DEG[];
constexpr int DVB_S2X_TABLE_C2::LEN[];
constexpr int DVB_S2X_TABLE_C2::POS[];

constexpr int DVB_S2X_TABLE_C3::DEG[];
constexpr int DVB_S2X_TABLE_C3::LEN[];
constexpr int DVB_S2X_TABLE_C3::POS[];

constexpr int DVB_S2X_TABLE_C4::DEG[];
constexpr int DVB_S2X_TABLE_C4::LEN[];
constexpr int DVB_S2X_TABLE_C4::POS[];

constexpr int DVB_S2X_TABLE_C5::DEG[];
constexpr int DVB_S2X_TABLE_C5::LEN[];
constexpr int DVB_S2X_TABLE_C5::POS[];

constexpr int DVB_S2X_TABLE_C6::DEG[];
constexpr int DVB_S2X_TABLE_C6::LEN[];
constexpr int DVB_S2X_TABLE_C6::POS[];

constexpr int DVB_S2X_TABLE_C7::DEG[];
constexpr int DVB_S2X_TABLE_C7::LEN[];
constexpr int DVB_S2X_TABLE_C7::POS[];

constexpr int DVB_S2X_TABLE_C8::DEG[];
constexpr int DVB_S2X_TABLE_C8::LEN[];
constexpr int DVB_S2X_TABLE_C8::POS[];

constexpr int DVB_S2X_TABLE_C9::DEG[];
constexpr int DVB_S2X_TABLE_C9::LEN[];
constexpr int DVB_S2X_TABLE_C9::POS[];

constexpr int DVB_S2X_TABLE_C10::DEG[];
constexpr int DVB_S2X_TABLE_C10::LEN[];
constexpr int DVB_S2X_TABLE_C10::POS[];

constexpr int DVB_T2_TABLE_A3::DEG[];
constexpr int DVB_T2_TABLE_A3::LEN[];
constexpr int DVB_T2_TABLE_A3::POS[];

constexpr int DVB_T2_TABLE_B3::DEG[];
constexpr int DVB_T2_TABLE_B3::LEN[];
constexpr int DVB_T2_TABLE_B3::POS[];

namespace gr {
  namespace dvbs2rx {

    ldpc_decoder_cb::sptr
    ldpc_decoder_cb::make(dvb_standard_t standard, dvb_framesize_t framesize, dvb_code_rate_t rate, dvb_constellation_t constellation, dvb_outputmode_t outputmode)
    {
      return gnuradio::get_initial_sptr
        (new ldpc_decoder_cb_impl(standard, framesize, rate, constellation, outputmode));
    }

    /*
     * The private constructor
     */
    ldpc_decoder_cb_impl::ldpc_decoder_cb_impl(dvb_standard_t standard, dvb_framesize_t framesize, dvb_code_rate_t rate, dvb_constellation_t constellation, dvb_outputmode_t outputmode)
      : gr::block("ldpc_decoder_cb",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
      unsigned int rows;
      if (framesize == FECFRAME_NORMAL) {
        frame_size = FRAME_SIZE_NORMAL;
        switch (rate) {
          case C1_4:
            nbch = 16200;
            ldpc = new LDPC<DVB_S2_TABLE_B1, int8_t, FACTOR>();
            break;
          case C1_3:
            nbch = 21600;
            ldpc = new LDPC<DVB_S2_TABLE_B2, int8_t, FACTOR>();
            break;
          case C2_5:
            nbch = 25920;
            ldpc = new LDPC<DVB_S2_TABLE_B3, int8_t, FACTOR>();
            break;
          case C1_2:
            nbch = 32400;
            q_val = 90;
            ldpc = new LDPC<DVB_S2_TABLE_B4, int8_t, FACTOR>();
            break;
          case C3_5:
            nbch = 38880;
            q_val = 72;
            ldpc = new LDPC<DVB_S2_TABLE_B5, int8_t, FACTOR>();
            break;
          case C2_3:
            nbch = 43200;
            q_val = 60;
            if (standard == STANDARD_DVBS2) {
              ldpc = new LDPC<DVB_S2_TABLE_B6, int8_t, FACTOR>();
            }
            else {
              ldpc = new LDPC<DVB_T2_TABLE_A3, int8_t, FACTOR>();
            }
            break;
          case C3_4:
            nbch = 48600;
            q_val = 45;
            ldpc = new LDPC<DVB_S2_TABLE_B7, int8_t, FACTOR>();
            break;
          case C4_5:
            nbch = 51840;
            q_val = 36;
            ldpc = new LDPC<DVB_S2_TABLE_B8, int8_t, FACTOR>();
            break;
          case C5_6:
            nbch = 54000;
            q_val = 30;
            ldpc = new LDPC<DVB_S2_TABLE_B9, int8_t, FACTOR>();
            break;
          case C8_9:
            nbch = 57600;
            ldpc = new LDPC<DVB_S2_TABLE_B10, int8_t, FACTOR>();
            break;
          case C9_10:
            nbch = 58320;
            ldpc = new LDPC<DVB_S2_TABLE_B11, int8_t, FACTOR>();
            break;
          case C2_9_VLSNR:
            nbch = 14400;
            ldpc = new LDPC<DVB_S2X_TABLE_B1, int8_t, FACTOR>();
            break;
          case C13_45:
            nbch = 18720;
            ldpc = new LDPC<DVB_S2X_TABLE_B2, int8_t, FACTOR>();
            break;
          case C9_20:
            nbch = 29160;
            ldpc = new LDPC<DVB_S2X_TABLE_B3, int8_t, FACTOR>();
            break;
          case C90_180:
            nbch = 32400;
            ldpc = new LDPC<DVB_S2X_TABLE_B11, int8_t, FACTOR>();
            break;
          case C96_180:
            nbch = 34560;
            ldpc = new LDPC<DVB_S2X_TABLE_B12, int8_t, FACTOR>();
            break;
          case C11_20:
            nbch = 35640;
            ldpc = new LDPC<DVB_S2X_TABLE_B4, int8_t, FACTOR>();
            break;
          case C100_180:
            nbch = 36000;
            ldpc = new LDPC<DVB_S2X_TABLE_B13, int8_t, FACTOR>();
            break;
          case C104_180:
            nbch = 37440;
            ldpc = new LDPC<DVB_S2X_TABLE_B14, int8_t, FACTOR>();
            break;
          case C26_45:
            nbch = 37440;
            ldpc = new LDPC<DVB_S2X_TABLE_B5, int8_t, FACTOR>();
            break;
          case C18_30:
            nbch = 38880;
            ldpc = new LDPC<DVB_S2X_TABLE_B22, int8_t, FACTOR>();
            break;
          case C28_45:
            nbch = 40320;
            ldpc = new LDPC<DVB_S2X_TABLE_B6, int8_t, FACTOR>();
            break;
          case C23_36:
            nbch = 41400;
            ldpc = new LDPC<DVB_S2X_TABLE_B7, int8_t, FACTOR>();
            break;
          case C116_180:
            nbch = 41760;
            ldpc = new LDPC<DVB_S2X_TABLE_B15, int8_t, FACTOR>();
            break;
          case C20_30:
            nbch = 43200;
            ldpc = new LDPC<DVB_S2X_TABLE_B23, int8_t, FACTOR>();
            break;
          case C124_180:
            nbch = 44640;
            ldpc = new LDPC<DVB_S2X_TABLE_B16, int8_t, FACTOR>();
            break;
          case C25_36:
            nbch = 45000;
            ldpc = new LDPC<DVB_S2X_TABLE_B8, int8_t, FACTOR>();
            break;
          case C128_180:
            nbch = 46080;
            ldpc = new LDPC<DVB_S2X_TABLE_B17, int8_t, FACTOR>();
            break;
          case C13_18:
            nbch = 46800;
            ldpc = new LDPC<DVB_S2X_TABLE_B9, int8_t, FACTOR>();
            break;
          case C132_180:
            nbch = 47520;
            ldpc = new LDPC<DVB_S2X_TABLE_B18, int8_t, FACTOR>();
            break;
          case C22_30:
            nbch = 47520;
            ldpc = new LDPC<DVB_S2X_TABLE_B24, int8_t, FACTOR>();
            break;
          case C135_180:
            nbch = 48600;
            ldpc = new LDPC<DVB_S2X_TABLE_B19, int8_t, FACTOR>();
            break;
          case C140_180:
            nbch = 50400;
            ldpc = new LDPC<DVB_S2X_TABLE_B20, int8_t, FACTOR>();
            break;
          case C7_9:
            nbch = 50400;
            ldpc = new LDPC<DVB_S2X_TABLE_B10, int8_t, FACTOR>();
            break;
          case C154_180:
            nbch = 55440;
            ldpc = new LDPC<DVB_S2X_TABLE_B21, int8_t, FACTOR>();
            break;
          default:
            break;
        }
      }
      else if (framesize == FECFRAME_SHORT) {
        frame_size = FRAME_SIZE_SHORT;
        switch (rate) {
          case C1_4:
            nbch = 3240;
            ldpc = new LDPC<DVB_S2_TABLE_C1, int8_t, FACTOR>();
            break;
          case C1_3:
            nbch = 5400;
            q_val = 30;
            ldpc = new LDPC<DVB_S2_TABLE_C2, int8_t, FACTOR>();
            break;
          case C2_5:
            nbch = 6480;
            q_val = 27;
            ldpc = new LDPC<DVB_S2_TABLE_C3, int8_t, FACTOR>();
            break;
          case C1_2:
            nbch = 7200;
            q_val = 25;
            ldpc = new LDPC<DVB_S2_TABLE_C4, int8_t, FACTOR>();
            break;
          case C3_5:
            nbch = 9720;
            q_val = 18;
            if (standard == STANDARD_DVBS2) {
              ldpc = new LDPC<DVB_S2_TABLE_C5, int8_t, FACTOR>();
            }
            else {
              ldpc = new LDPC<DVB_T2_TABLE_B3, int8_t, FACTOR>();
            }
            break;
          case C2_3:
            nbch = 10800;
            q_val = 15;
            ldpc = new LDPC<DVB_S2_TABLE_C6, int8_t, FACTOR>();
            break;
          case C3_4:
            nbch = 11880;
            q_val = 12;
            ldpc = new LDPC<DVB_S2_TABLE_C7, int8_t, FACTOR>();
            break;
          case C4_5:
            nbch = 12600;
            q_val = 10;
            ldpc = new LDPC<DVB_S2_TABLE_C8, int8_t, FACTOR>();
            break;
          case C5_6:
            nbch = 13320;
            q_val = 8;
            ldpc = new LDPC<DVB_S2_TABLE_C9, int8_t, FACTOR>();
            break;
          case C8_9:
            nbch = 14400;
            ldpc = new LDPC<DVB_S2_TABLE_C10, int8_t, FACTOR>();
            break;
          case C11_45:
            nbch = 3960;
            ldpc = new LDPC<DVB_S2X_TABLE_C1, int8_t, FACTOR>();
            break;
          case C4_15:
            nbch = 4320;
            ldpc = new LDPC<DVB_S2X_TABLE_C2, int8_t, FACTOR>();
            break;
          case C14_45:
            nbch = 5040;
            ldpc = new LDPC<DVB_S2X_TABLE_C3, int8_t, FACTOR>();
            break;
          case C7_15:
            nbch = 7560;
            ldpc = new LDPC<DVB_S2X_TABLE_C4, int8_t, FACTOR>();
            break;
          case C8_15:
            nbch = 8640;
            ldpc = new LDPC<DVB_S2X_TABLE_C5, int8_t, FACTOR>();
            break;
          case C26_45:
            nbch = 9360;
            ldpc = new LDPC<DVB_S2X_TABLE_C6, int8_t, FACTOR>();
            break;
          case C32_45:
            nbch = 11520;
            ldpc = new LDPC<DVB_S2X_TABLE_C7, int8_t, FACTOR>();
            break;
          case C1_5_VLSNR_SF2:
            nbch = 2680;
            ldpc = new LDPC<DVB_S2_TABLE_C1, int8_t, FACTOR>();
            break;
          case C11_45_VLSNR_SF2:
            nbch = 3960;
            ldpc = new LDPC<DVB_S2X_TABLE_C1, int8_t, FACTOR>();
            break;
          case C1_5_VLSNR:
            nbch = 3240;
            ldpc = new LDPC<DVB_S2_TABLE_C1, int8_t, FACTOR>();
            break;
          case C4_15_VLSNR:
            nbch = 4320;
            ldpc = new LDPC<DVB_S2X_TABLE_C2, int8_t, FACTOR>();
            break;
          case C1_3_VLSNR:
            nbch = 5400;
            ldpc = new LDPC<DVB_S2_TABLE_C2, int8_t, FACTOR>();
            break;
          default:
            nbch = 0;
            break;
        }
      }
      else {
        frame_size = FRAME_SIZE_MEDIUM;
        switch (rate) {
          case C1_5_MEDIUM:
            nbch = 5840;
            ldpc = new LDPC<DVB_S2X_TABLE_C8, int8_t, FACTOR>();
            break;
          case C11_45_MEDIUM:
            nbch = 7920;
            ldpc = new LDPC<DVB_S2X_TABLE_C9, int8_t, FACTOR>();
            break;
          case C1_3_MEDIUM:
            nbch = 10800;
            ldpc = new LDPC<DVB_S2X_TABLE_C10, int8_t, FACTOR>();
            break;
          default:
            nbch = 0;
            break;
        }
      }
      switch (constellation) {
        case MOD_QPSK:
          mod = new PhaseShiftKeying<4, gr_complex, int8_t>();
          break;
        case MOD_8PSK:
          mod = new PhaseShiftKeying<8, gr_complex, int8_t>();
          rows = ldpc->code_len() / mod->bits();
          /* 210 */
          if (rate == C3_5) {
            rowaddr0 = rows * 2;
            rowaddr1 = rows;
            rowaddr2 = 0;
          }
          /* 102 */
          else if (rate == C25_36 || rate == C13_18 || rate == C7_15 || rate == C8_15 || rate == C26_45) {
            rowaddr0 = rows;
            rowaddr1 = 0;
            rowaddr2 = rows * 2;
          }
          /* 012 */
          else {
            rowaddr0 = 0;
            rowaddr1 = rows;
            rowaddr2 = rows * 2;
          }
          break;
        case MOD_16QAM:
          mod = new QuadratureAmplitudeModulation<16, gr_complex, int8_t>();
          break;
        case MOD_64QAM:
          mod = new QuadratureAmplitudeModulation<64, gr_complex, int8_t>();
          break;
        case MOD_256QAM:
          mod = new QuadratureAmplitudeModulation<256, gr_complex, int8_t>();
          break;
        default:
          break;
      }
      frame = 0;
      signal_constellation = constellation;
      code_rate = rate;
      dvb_standard = standard;
      output_mode = outputmode;
      if (outputmode == OM_MESSAGE) {
        set_output_multiple(nbch);
      }
      else {
        set_output_multiple(frame_size);
      }
    }

    /*
     * Our virtual destructor.
     */
    ldpc_decoder_cb_impl::~ldpc_decoder_cb_impl()
    {
      delete mod;
      delete ldpc;
    }

    void
    ldpc_decoder_cb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      if (output_mode == OM_MESSAGE) {
        ninput_items_required[0] = (noutput_items / nbch) * (frame_size / mod->bits());
      }
      else {
        ninput_items_required[0] = noutput_items / mod->bits();
      }
    }

    int
    ldpc_decoder_cb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      int8_t soft[ldpc->code_len()];
      int8_t dint[ldpc->code_len()];
      int8_t tempu[ldpc->code_len()];
      int8_t tempv[ldpc->code_len()];
      int8_t tmp[mod->bits()];
      int8_t *code;
      float sp, np, sigma, precision, snr;
      gr_complex s, e;
      const int SYMBOLS = ldpc->code_len() / mod->bits();
      int trials = 50;
      int consumed = 0;
      int rows, offset, indexin, indexout;
      const int *twist;
      const int *mux;
      int8_t *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8, *c9, *c10, *c11, *c12, *c13, *c14, *c15, *c16;
      int output_size = output_mode ? nbch : frame_size;

      for (int i = 0; i < noutput_items; i += output_size) {
        sp = 0;
        np = 0;
        for (int j = 0; j < SYMBOLS; j++) {
          mod->hard(tmp, in[j]);
          s = mod->map(tmp);
          e = in[j] - s;
          sp += std::norm(s);
          np += std::norm(e);
        }
        if (!(np > 0)) {
          np = 1e-12;
        }
        snr = 10 * std::log10(sp / np);
        sigma = std::sqrt(np / (2 * sp));
        precision = FACTOR / (sigma * sigma);
        for (int j = 0; j < SYMBOLS; j++) {
          mod->soft(soft + (j * mod->bits()), in[j], precision);
        }
        switch (signal_constellation) {
          case MOD_QPSK:
            if (dvb_standard == STANDARD_DVBT2) {
              if (code_rate == C1_3 || code_rate == C2_5) {
                for (unsigned int t = 0; t < q_val; t++) {
                  for (int s = 0; s < 360; s++) {
                    dint[nbch + (q_val * s) + t] = soft[nbch + (360 * t) + s];
                  }
                }
                for (unsigned int k = 0; k < nbch; k++) {
                  dint[k] = soft[k];
                }
                code = dint;
              }
              else {
                code = soft;
              }
            }
            else {
              code = soft;
            }
            break;
          case MOD_8PSK:
            rows = frame_size / mod->bits();
            c1 = &dint[rowaddr0];
            c2 = &dint[rowaddr1];
            c3 = &dint[rowaddr2];
            indexin = 0;
            for (int j = 0; j < rows; j++) {
              c1[j] = soft[indexin++];
              c2[j] = soft[indexin++];
              c3[j] = soft[indexin++];
            }
            code = dint;
            break;
          case MOD_16QAM:
            if (frame_size == FRAME_SIZE_NORMAL) {
              twist = &twist16n[0];
            }
            else {
              twist = &twist16s[0];
            }
            if (code_rate == C3_5 && frame_size == FRAME_SIZE_NORMAL) {
              mux = &mux16_35[0];
            }
            else if (code_rate == C1_3 && frame_size == FRAME_SIZE_SHORT) {
              mux = &mux16_13[0];
            }
            else if (code_rate == C2_5 && frame_size == FRAME_SIZE_SHORT) {
              mux = &mux16_25[0];
            }
            else {
              mux = &mux16[0];
            }
            rows = frame_size / (mod->bits() * 2);
            c1 = &tempv[0];
            c2 = &tempv[rows];
            c3 = &tempv[rows * 2];
            c4 = &tempv[rows * 3];
            c5 = &tempv[rows * 4];
            c6 = &tempv[rows * 5];
            c7 = &tempv[rows * 6];
            c8 = &tempv[rows * 7];
            indexin = 0;
            indexout = 0;
            for (unsigned int d = 0; d < frame_size / (mod->bits() * 2); d++) {
              for (int e = 0; e < (mod->bits() * 2); e++) {
                offset = mux[e];
                tempu[indexout++] = soft[offset + indexin];
              }
              indexin += mod->bits() * 2;
            }
            indexin = 0;
            for (int j = 0; j < rows; j++) {
              c1[j] = tempu[indexin++];
              c2[j] = tempu[indexin++];
              c3[j] = tempu[indexin++];
              c4[j] = tempu[indexin++];
              c5[j] = tempu[indexin++];
              c6[j] = tempu[indexin++];
              c7[j] = tempu[indexin++];
              c8[j] = tempu[indexin++];
            }
            indexout = 0;
            for (int col = 0; col < (mod->bits() * 2); col++) {
              offset = twist[col];
              for (int row = 0; row < rows; row++) {
                tempu[indexout++] = tempv[offset + (rows * col)];
                offset++;
                if (offset == rows) {
                  offset = 0;
                }
              }
            }
            for (unsigned int t = 0; t < q_val; t++) {
              for (int s = 0; s < 360; s++) {
                dint[nbch + (q_val * s) + t] = tempu[nbch + (360 * t) + s];
              }
            }
            for (unsigned int k = 0; k < nbch; k++) {
              dint[k] = tempu[k];
            }
            code = dint;
            break;
          case MOD_64QAM:
            if (frame_size == FRAME_SIZE_NORMAL) {
              twist = &twist64n[0];
            }
            else {
              twist = &twist64s[0];
            }
            if (code_rate == C3_5 && frame_size == FRAME_SIZE_NORMAL) {
              mux = &mux64_35[0];
            }
            else if (code_rate == C1_3 && frame_size == FRAME_SIZE_SHORT) {
              mux = &mux64_13[0];
            }
            else if (code_rate == C2_5 && frame_size == FRAME_SIZE_SHORT) {
              mux = &mux64_25[0];
            }
            else {
              mux = &mux64[0];
            }
            rows = frame_size / (mod->bits() * 2);
            c1 = &tempv[0];
            c2 = &tempv[rows];
            c3 = &tempv[rows * 2];
            c4 = &tempv[rows * 3];
            c5 = &tempv[rows * 4];
            c6 = &tempv[rows * 5];
            c7 = &tempv[rows * 6];
            c8 = &tempv[rows * 7];
            c9 = &tempv[rows * 8];
            c10 = &tempv[rows * 9];
            c11 = &tempv[rows * 10];
            c12 = &tempv[rows * 11];
            indexin = 0;
            indexout = 0;
            for (unsigned int d = 0; d < frame_size / (mod->bits() * 2); d++) {
              for (int e = 0; e < (mod->bits() * 2); e++) {
                offset = mux[e];
                tempu[indexout++] = soft[offset + indexin];
              }
              indexin += mod->bits() * 2;
            }
            indexin = 0;
            for (int j = 0; j < rows; j++) {
              c1[j] = tempu[indexin++];
              c2[j] = tempu[indexin++];
              c3[j] = tempu[indexin++];
              c4[j] = tempu[indexin++];
              c5[j] = tempu[indexin++];
              c6[j] = tempu[indexin++];
              c7[j] = tempu[indexin++];
              c8[j] = tempu[indexin++];
              c9[j] = tempu[indexin++];
              c10[j] = tempu[indexin++];
              c11[j] = tempu[indexin++];
              c12[j] = tempu[indexin++];
            }
            indexout = 0;
            for (int col = 0; col < (mod->bits() * 2); col++) {
              offset = twist[col];
              for (int row = 0; row < rows; row++) {
                tempu[indexout++] = tempv[offset + (rows * col)];
                offset++;
                if (offset == rows) {
                  offset = 0;
                }
              }
            }
            for (unsigned int t = 0; t < q_val; t++) {
              for (int s = 0; s < 360; s++) {
                dint[nbch + (q_val * s) + t] = tempu[nbch + (360 * t) + s];
              }
            }
            for (unsigned int k = 0; k < nbch; k++) {
              dint[k] = tempu[k];
            }
            code = dint;
            break;
          case MOD_256QAM:
            if (frame_size == FRAME_SIZE_NORMAL) {
              twist = &twist256n[0];
              if (code_rate == C3_5) {
                mux = &mux256_35[0];
              }
              else if (code_rate == C2_3) {
                mux = &mux256_23[0];
              }
              else {
                mux = &mux256[0];
              }
              rows = frame_size / (mod->bits() * 2);
              c1 = &tempv[0];
              c2 = &tempv[rows];
              c3 = &tempv[rows * 2];
              c4 = &tempv[rows * 3];
              c5 = &tempv[rows * 4];
              c6 = &tempv[rows * 5];
              c7 = &tempv[rows * 6];
              c8 = &tempv[rows * 7];
              c9 = &tempv[rows * 8];
              c10 = &tempv[rows * 9];
              c11 = &tempv[rows * 10];
              c12 = &tempv[rows * 11];
              c13 = &tempv[rows * 12];
              c14 = &tempv[rows * 13];
              c15 = &tempv[rows * 14];
              c16 = &tempv[rows * 15];
              indexin = 0;
              indexout = 0;
              for (unsigned int d = 0; d < frame_size / (mod->bits() * 2); d++) {
                for (int e = 0; e < (mod->bits() * 2); e++) {
                  offset = mux[e];
                  tempu[indexout++] = soft[offset + indexin];
                }
                indexin += mod->bits() * 2;
              }
              indexin = 0;
              for (int j = 0; j < rows; j++) {
                c1[j] = tempu[indexin++];
                c2[j] = tempu[indexin++];
                c3[j] = tempu[indexin++];
                c4[j] = tempu[indexin++];
                c5[j] = tempu[indexin++];
                c6[j] = tempu[indexin++];
                c7[j] = tempu[indexin++];
                c8[j] = tempu[indexin++];
                c9[j] = tempu[indexin++];
                c10[j] = tempu[indexin++];
                c11[j] = tempu[indexin++];
                c12[j] = tempu[indexin++];
                c13[j] = tempu[indexin++];
                c14[j] = tempu[indexin++];
                c15[j] = tempu[indexin++];
                c16[j] = tempu[indexin++];
              }
              indexout = 0;
              for (int col = 0; col < (mod->bits() * 2); col++) {
                offset = twist[col];
                for (int row = 0; row < rows; row++) {
                  tempu[indexout++] = tempv[offset + (rows * col)];
                  offset++;
                  if (offset == rows) {
                    offset = 0;
                  }
                }
              }
              for (unsigned int t = 0; t < q_val; t++) {
                for (int s = 0; s < 360; s++) {
                  dint[nbch + (q_val * s) + t] = tempu[nbch + (360 * t) + s];
                }
              }
              for (unsigned int k = 0; k < nbch; k++) {
                dint[k] = tempu[k];
              }
              code = dint;
            }
            else {
              twist = &twist256s[0];
              if (code_rate == C1_3) {
                mux = &mux256s_13[0];
              }
              else if (code_rate == C2_5) {
                mux = &mux256s_25[0];
              }
              else {
                mux = &mux256s[0];
              }
              rows = frame_size / mod->bits();
              c1 = &tempv[0];
              c2 = &tempv[rows];
              c3 = &tempv[rows * 2];
              c4 = &tempv[rows * 3];
              c5 = &tempv[rows * 4];
              c6 = &tempv[rows * 5];
              c7 = &tempv[rows * 6];
              c8 = &tempv[rows * 7];
              indexin = 0;
              indexout = 0;
              for (unsigned int d = 0; d < frame_size / mod->bits(); d++) {
                for (int e = 0; e < mod->bits(); e++) {
                  offset = mux[e];
                  tempu[indexout++] = soft[offset + indexin];
                }
                indexin += mod->bits();
              }
              indexin = 0;
              for (int j = 0; j < rows; j++) {
                c1[j] = tempu[indexin++];
                c2[j] = tempu[indexin++];
                c3[j] = tempu[indexin++];
                c4[j] = tempu[indexin++];
                c5[j] = tempu[indexin++];
                c6[j] = tempu[indexin++];
                c7[j] = tempu[indexin++];
                c8[j] = tempu[indexin++];
              }
              indexout = 0;
              for (int col = 0; col < mod->bits(); col++) {
                offset = twist[col];
                for (int row = 0; row < rows; row++) {
                  tempu[indexout++] = tempv[offset + (rows * col)];
                  offset++;
                  if (offset == rows) {
                    offset = 0;
                  }
                }
              }
              for (unsigned int t = 0; t < q_val; t++) {
                for (int s = 0; s < 360; s++) {
                  dint[nbch + (q_val * s) + t] = tempu[nbch + (360 * t) + s];
                }
              }
              for (unsigned int k = 0; k < nbch; k++) {
                dint[k] = tempu[k];
              }
              code = dint;
            }
            break;
          default:
            code = soft;
            break;
        }
        int count = ldpc->decode(code, code + ldpc->data_len(), trials);
        if (count < 0) {
          printf("frame = %d, snr = %.2f, LDPC decoder failed at converging to a code word.\n", frame, snr);
        }
        else {
          printf("frame = %d, snr = %.2f, trials = %d\n", frame, snr, trials - count);
        }
        frame++;
        for (int j = 0; j < output_size; j++) {
          if (code[j] >= 0) {
            *out++ = 0;
          }
          else {
            *out++ = 1;
          }
        }
        in += frame_size / mod->bits();
        consumed += frame_size / mod->bits();
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (consumed);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    const int ldpc_decoder_cb_impl::twist16n[8] =
    {
      0, 0, 2, 4, 4, 5, 7, 7
    };

    const int ldpc_decoder_cb_impl::twist64n[12] =
    {
      0, 0, 2, 2, 3, 4, 4, 5, 5, 7, 8, 9
    };

    const int ldpc_decoder_cb_impl::twist256n[16] =
    {
      0, 2, 2, 2, 2, 3, 7, 15, 16, 20, 22, 22, 27, 27, 28, 32
    };

    const int ldpc_decoder_cb_impl::twist16s[8] =
    {
      0, 0, 0, 1, 7, 20, 20, 21
    };

    const int ldpc_decoder_cb_impl::twist64s[12] =
    {
      0, 0, 0, 2, 2, 2, 3, 3, 3, 6, 7, 7
    };

    const int ldpc_decoder_cb_impl::twist256s[8] =
    {
      0, 0, 0, 1, 7, 20, 20, 21
    };

    const int ldpc_decoder_cb_impl::mux16[8] =
    {
      7, 1, 4, 2, 5, 3, 6, 0
    };

    const int ldpc_decoder_cb_impl::mux64[12] =
    {
      11, 7, 3, 10, 6, 2, 9, 5, 1, 8, 4, 0
    };

    const int ldpc_decoder_cb_impl::mux256[16] =
    {
      15, 1, 13, 3, 8, 11, 9, 5, 10, 6, 4, 7, 12, 2, 14, 0
    };

    const int ldpc_decoder_cb_impl::mux16_35[8] =
    {
      0, 5, 1, 2, 4, 7, 3, 6
    };

    const int ldpc_decoder_cb_impl::mux16_13[8] =
    {
      6, 0, 3, 4, 5, 2, 1, 7
    };

    const int ldpc_decoder_cb_impl::mux16_25[8] =
    {
      7, 5, 4, 0, 3, 1, 2, 6
    };

    const int ldpc_decoder_cb_impl::mux64_35[12] =
    {
      2, 7, 6, 9, 0, 3, 1, 8, 4, 11, 5, 10
    };

    const int ldpc_decoder_cb_impl::mux64_13[12] =
    {
      4, 2, 0, 5, 6, 1, 3, 7, 8, 9, 10, 11
    };

    const int ldpc_decoder_cb_impl::mux64_25[12] =
    {
      4, 0, 1, 6, 2, 3, 5, 8, 7, 10, 9, 11
    };

    const int ldpc_decoder_cb_impl::mux256_35[16] =
    {
      2, 11, 3, 4, 0, 9, 1, 8, 10, 13, 7, 14, 6, 15, 5, 12
    };

    const int ldpc_decoder_cb_impl::mux256_23[16] =
    {
      7, 2, 9, 0, 4, 6, 13, 3, 14, 10, 15, 5, 8, 12, 11, 1
    };

    const int ldpc_decoder_cb_impl::mux256s[8] =
    {
      7, 3, 1, 5, 2, 6, 4, 0
    };

    const int ldpc_decoder_cb_impl::mux256s_13[8] =
    {
      4, 0, 1, 2, 5, 3, 6, 7
    };

    const int ldpc_decoder_cb_impl::mux256s_25[8] =
    {
      4, 0, 5, 1, 2, 3, 6, 7
    };

  } /* namespace dvbs2rx */
} /* namespace gr */
