#include "PID.h"
typedef struct {
		double Kp;
		double Ki;
		double Kd;
		double intergrator;
}PID_Var;



// ----- Angular Displacement ------
PID_Var Angular_Disp;
void Set_Angular_Disp_Const(double pConst, double iConst, double dConst) {
		Angular_Disp.Kp = pConst;
		Angular_Disp.Ki = iConst;
		Angular_Disp.Kd = dConst;
}

void init_Angular_Disp_PID(double pConst, double iConst, double dConst) {
		Set_Angular_Disp_Const(pConst, iConst, dConst);
		Angular_Disp.intergrator = 0.000f;
		//[add] get d measurements
		
}

double Angular_Disp_Perr() {
		
}
double Angular_Disp_Ierr() {
		
}
double Angular_Disp_Derr() {
		
}

double Angular_Disp_PID_OUTPUT(void) {
		return Angular_Disp.Kp * Angular_Disp_Perr() +
					 Angular_Disp.Ki * Angular_Disp_Ierr() +
					 Angular_Disp.Kd * Angular_Disp_Derr();
}









