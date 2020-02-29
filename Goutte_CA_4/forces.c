// forces.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "params.h" 
#include "forces.h"

// forces and velocities
// This is problem-specific

// q[0] = theta_1
// q[1] = theta_2
// q[2] = p_1
// q[4] = p_2

// d theta_1 /dt
// first equation for double pendulum
double QVelo0(double *q, double t, int num_elems)
{
	// declare variables
	double f;
	double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
	double cos12, Mtot;

	// translate into readables
	Translate(q, &theta_1, &theta_2, &p_1, &p_2, 
		&m_1, &m_2, &l_1, &l_2);

	// angle between 1 and 2
	cos12 = cos(theta_1 - theta_2);

	// total mass
	Mtot = m_1 + m_2;

	// implement
	f = l_2*p_1 - l_1*p_2*cos12;
	f /= l_1*l_1*l_2*(Mtot - m_2*cos12*cos12);

	return f;

} //QVelo0

// d theta_2 /dt
double QVelo1(double *q, double t, int num_elems)
{
	// declare variables
	double f;
	double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
	double cos12, Mtot;

	// translate into readables
	Translate(q, &theta_1, &theta_2, &p_1, &p_2, 
		&m_1, &m_2, &l_1, &l_2);

	// angle between 1 and 2
	cos12 = cos(theta_1 - theta_2);

	// total mass
	Mtot = m_1 + m_2;

	// implement
	f = l_1*Mtot*p_2 - l_2*m_2*p_1*cos12;
	f /= l_1*l_2*l_2*m_2*(Mtot - m_2*cos12*cos12);
	
	return f;

} //QVelo1

// d p_1 /dt
double QVelo2(double *q, double t, int num_elems)
{
	// declare variables
	double f;
	double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
	double cos12, sin12, Mtot;
	double term_1, term_2, term_3;
	double g = 9.8;

	// translate into readables
	Translate(q, &theta_1, &theta_2, &p_1, &p_2, 
		&m_1, &m_2, &l_1, &l_2);

	// angle between 1 and 2
	cos12 = cos(theta_1 - theta_2);
	sin12 = sin(theta_1 - theta_2);

	// total mass
	Mtot = m_1 + m_2;

	// implement
	term_1 = p_1*p_2*sin12;
	term_1 /= l_1*l_2*(Mtot - m_2*cos12*cos12);
	
	term_2 = (l_2/l_1)*p_1*p_1 + 
	(l_1/l_2)*(Mtot/m_2)*p_2*p_2 -
	2*p_1*p_2*cos12;
	term_2 /= l_2*l_1*pow((Mtot - m_2*cos12*cos12),2);
	term_2 *= m_2*cos12*sin12;

	term_3 = Mtot*g*l_1*sin(theta_1);

	f = -1.*term_1 + term_2 - term_3;

	return f;

} //QVelo2

// d p_2 /dt
double QVelo3(double *q, double t, int num_elems)
{
	// declare variables
	double f;
	double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
	double cos12, sin12, Mtot;
	double term_1, term_2, term_3;
	double g = 9.8;

	// translate into readables
	Translate(q, &theta_1, &theta_2, &p_1, &p_2, 
		&m_1, &m_2, &l_1, &l_2);

	// angle between 1 and 2
	cos12 = cos(theta_1 - theta_2);

	// total mass
	Mtot = m_1 + m_2;

	// implement
	term_1 = p_1*p_2*sin12;
	term_1 /= l_1*l_2*(Mtot - m_2*cos12*cos12);
	
	term_2 = (l_2/l_1)*p_1*p_1 + 
	(l_1/l_2)*(Mtot/m_2)*p_2*p_2 -
	2*p_1*p_2*cos12;
	term_2 /= l_2*l_1*pow((Mtot - m_2*cos12*cos12),2);
	term_2 *= m_2*cos12*sin12;

	term_3 = m_2*g*l_2*sin(theta_2);

	f = term_1 - term_2 - term_3;

	return f;

} //QVelo3

void Translate(double *q, double *theta_1, double *theta_2, 
	double *p_1, double *p_2, double *mass1, double *mass2, 
	double *length1, double *length2)
{
	theta_1 = q[0];
	theta_2 = q[1];
	p_1 = q[2];
	p_2 = q[3];

	mass1 = PARAM_DATA.mass1;
	mass2 = PARAM_DATA.mass2;
	length1 = PARAM_DATA.length1;
	length2 = PARAM_DATA.length2;

	return;
} // Translate

double TotalEnergy(double *q)
{
	// declare variables
	double g = 9.8;
	double H;
	double cos12, Mtot;
	double term_1, term_2, term_3;

	// translate into readables
	Translate(q, &theta_1, &theta_2, &p_1, &p_2, 
		&m_1, &m_2, &l_1, &l_2);

	// angle between 1 and 2
	cos12 = cos(theta_1 - theta_2);

	// total mass
	Mtot = m_1 + m_2;

	// implement
	term_1 = (l_2/l_1)*p_1*p_1 + 
	(l_1/l_2)*(Mtot/m_2)*p_2*p_2 -
	2*p_1*p_2*cos12;
	term_1 /= l_2*l_1*pow((Mtot - m_2*cos12*cos12),2);

	term_2 = Mtot*g*l_1*cos(theta_1);

	term_3 = m_2*g*l_2*cos(theta_2);

	H = term_1 - term_2 - term_3;

	return H;
} // TotalEnergy
















