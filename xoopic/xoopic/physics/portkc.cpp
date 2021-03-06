/*
====================================================================

PORT.CPP

0.99	(NTG 12-29-93) Separated into individual module from pic.h.
0.991	(JohnV 01-03-93) Aesthetics, compile.
0.992	(JohnV 03-23-94) Streamline includes, remove pic.h.

====================================================================
*/

#include "port.h"
#include	"fields.h"
#include "ptclgrp.h"

Port::Port(int j1, int k1, int j2, int k2, int normal) : Boundary(j1, k1, j2, k2, normal)
{
//	no code yet
}

//--------------------------------------------------------------------
//	Apply boundary conditions to fields locally.

Scalar	AnalyticEz(Scalar z, Scalar r, Scalar f, Scalar t, Scalar a);
Scalar	AnalyticEr(Scalar z, Scalar r, Scalar f, Scalar t, Scalar a);
Scalar	AnalyticBphi(Scalar z, Scalar r, Scalar f, Scalar t, Scalar a);

void Port::applyFields(Scalar t,Scalar dt)
{
   if(dt==0) return;
if (t<2E-10)
  {
    Grid*  grid = fields->get_grid();
    Scalar freq = 10E9;
    Scalar zforEz = (grid->getMKS(j1 + 1, k1).e1()
		+ grid->getMKS(j1, k1).e1())/2.0;
    Scalar zforEr = grid->getMKS(j1, k1).e1();
    Scalar a = grid->getMKS(0, grid->getK()).e2();
    for (int k = k1; k <= k2; k++)
      {
	Scalar	rforEz = grid->getMKS(j1, k).e2();
   	Scalar	intEz = grid->dl1(j1, k)
	  *AnalyticEz(zforEz, rforEz, freq, t, a);
   	fields->setIntEdl(j1, k, 1, intEz);
   	if (k < k2)
	  {
	    Scalar rforEr = (grid->getMKS(j1, k + 1).e2() +
			     grid->getMKS(j1, k).e2())/2.0;
	    Scalar intEr = grid->dl2(j1, k)*
			AnalyticEr(zforEr, rforEr, freq, t, a);
	    fields->setIntEdl(j1, k, 2, intEr);
	  }
      }
  }
}

//--------------------------------------------------------------------
//	Set the passive bc for fields at the port.  Currently just a
//	copy of those for conductor.

void Port::setPassives()
{
	int	inc;
	if (alongx2())								//	vertical
	{
		for (int k=MIN(k1,k2); k<MAX(k1,k2); k++)
		{
			fields->set_iC2(j1, k, 0);       	
			fields->set_iC3(j1, k, 0);
		}
		fields->set_iC3(j1, k2, 0);
	}
	else											//	horizontal
	{
		for (int j=MIN(j1,j2); j<MAX(j1,j2); j++)
      {
			fields->set_iC1(j, k1, 0);
			fields->set_iC3(j, k1, 0);
		}
		fields->set_iC3(j2, k1, 0);
	}
}

//--------------------------------------------------------------------
//	Port::emit() simply deletes Particles in its stack.  May add some
//	diagnostics for particles collected in the future.
#ifndef __linux__
#pragma argsused
#endif
ParticleList& Port::emit(Scalar t,Scalar dt)
{
	while(!particleList.isEmpty())
	{
		Particle* p = particleList.pop();
		delete p;
	}
   return particleList;
}

