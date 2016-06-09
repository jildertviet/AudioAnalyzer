
#ifndef _FILTER_H
#define _FILTER_H

#define MAX_NUM_FILTER_TAPS 1000

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>

enum filterType {LPF, HPF, BPF};

class Filter{
	private:
		filterType m_filt_t;
		int m_num_taps;
		int m_error_flag;
		double m_Fs;
		double m_Fx;
		double m_lambda;
		double *m_taps;
		double *m_sr;
		void designLPF();
		void designHPF();

		// Only needed for the bandpass filter case
		double m_Fu, m_phi;
		void designBPF();

	public:
		Filter(filterType filt_t, int num_taps, double Fs, double Fx);
		Filter(filterType filt_t, int num_taps, double Fs, double Fl, double Fu);
		~Filter( );
		void init();
		double do_sample(double data_sample);
		int get_error_flag(){return m_error_flag;};
		void get_taps( double *taps );
		int write_taps_to_file( char* filename );
		int write_freqres_to_file( char* filename );
};

#endif
