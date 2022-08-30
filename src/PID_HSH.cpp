#include "PID_HSH.h"

PID_HSH::PID_HSH(double kp, double ki, double kd, unsigned int dT, double* control, double* measure, double* target){
    _kp = kp;
    _ki = ki;
    _kd = kd;    
    _control = control;
    _measure = measure;
    _target = target;    

    setPeriodinMicroseconds(dT);
    setScaler(1.0);
    setControlLimits(0, 255);    
}

PID_HSH::PID_HSH(){
    _kp = 1.0;
    _ki = 0.0;
    _kd = 0.0;    
    _control = nullptr;
    _measure = nullptr;
    _target = nullptr;    
        
    setPeriodinMicroseconds(1000);
    setScaler(1.0);
    setControlLimits(0, 255);
}

void PID_HSH::computePID(){
    computePID(_dTSec);
}

void PID_HSH::computePID(unsigned int passedTimeMicros){
    computePID(passedTimeMicros / 1000000.0);
}

void PID_HSH::computePID(double passedSec){
    _err = (*_target) - (*_measure);
    _errSum += _err * passedSec;
    _derr = (_err - _perr) / passedSec;

    if (_errSum > _AntiWindup){
        _errSum = _AntiWindup;
    }
    
    double output = _kp * _err + _ki * _errSum + _kd * _derr;
    output *= _scaler;    
    
    if (output > _controlMax){
        output = _controlMax;
    }
    else if (output < _controlMin){
        output = _controlMin;
    }

    _perr = _err;
    *_control = output;        
    return;
}

void PID_HSH::setPIDCoeffs(double pgain, double igain, double dgain){
    _kp = pgain;
    _ki = igain;
    _kd = dgain;
}

void PID_HSH:: setPIDBuffers(double* control, double* measure, double* target){
    _control = control;
    _measure = measure;
    _target = target;
}

void PID_HSH::setControlLimits(double contMax, double contMin){
    _controlMax = contMax;
    _controlMin = contMin;
    return;
}

void PID_HSH::setAntiWindup(double aw){
    _AntiWindup = aw;
    return;
}

void PID_HSH::setPeriodinMicroseconds(unsigned int micros){
    _dTSec = micros / 1000000;    
}

void PID_HSH::setPeriodinMilliseconds(unsigned int millis){
    _dTSec = millis / 1000;    
}

void PID_HSH::setScaler(double scaler){
    _scaler = scaler;
}

double PID_HSH::getPgain(){    
    return _kp;
}
double PID_HSH::getIgain(){    
    return _ki;
}
double PID_HSH::getDgain(){    
    return _kd;
}
double PID_HSH::getAW(){
    return _AntiWindup;
}    
double PID_HSH::getPeriodinSec(){
    return _dTSec;
}
double PID_HSH::getErr(){
    return _err;
}
double PID_HSH::getErrSum(){
    return _errSum;
}
double PID_HSH::getDiffErr(){
    return _derr;
}
