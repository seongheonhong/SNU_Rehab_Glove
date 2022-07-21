#ifndef PID_H
#define PID_H
#define FORWARD_DIR true
#define REVERSE_DIR false

class PID_HSH
{
public:
    PID_HSH(double, double, double, unsigned int, double*, double*, double*);
    bool updatePID();
    void setAntiWindup(double);
    void setPIDCoeffs(double, double, double);
    void setPeriodinMicroseconds(unsigned int);
    void setPeriodinMilliseconds(unsigned int);
    void setControlLimits(double, double);
    void setScaler(double);
    void computePID();
    void computePID(unsigned int);
    void computePID(double);

    double getPgain();
    double getIgain();
    double getDgain();    
    double getAW();    
    double getPeriodinSec();
    double getErr();
    double getErrSum();
    double getDiffErr();

private:
    double _kp;
    double _ki;
    double _kd;
    double _scaler = 0.0;
    double _AntiWindup = 1E+20;    
    double _dTSec;

    double _err;
    double _perr = 0.0;
    double _errSum = 0.0;
    double _derr = 0.0;

    double* _control;
    double* _measure;
    double* _target;

    double _controlMax;
    double _controlMin;    
};

#endif
