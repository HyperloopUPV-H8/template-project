#pragma once
namespace BLCU{

/* enumeration of all possible boot targets
 * Micro-Fit 1 is the closest to the LAN adapter */

	enum Target{
		VCU,			//Micro-Fit 1
		OBCCU,			//			2
		BMSA,			//			3
		LCUM,			//			4
		LCUS,			//			5
		PCU,			//Micro-Fit 6
		NOTARGET,
	};
}

