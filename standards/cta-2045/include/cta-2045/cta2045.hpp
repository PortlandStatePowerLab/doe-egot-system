#pragma once
# include <cta2045/cta2045handler.hpp>




class CTA2045 {
	public:
		CTA2045();
		~CTA2045();
		int get_energy();
	private:		
		CTA2045Handler* device;
};