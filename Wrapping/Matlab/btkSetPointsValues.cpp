/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009-2015, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "btkMEXObjectHandle.h"

#include <btkAcquisition.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  if (nrhs != 2)
    mexErrMsgTxt("Two inputs required.");

  btkMXCheckNoOuput(nlhs, plhs); // Only when there is no output for the function.

  if ((mxGetClassID(prhs[1]) != mxDOUBLE_CLASS) || mxIsEmpty(prhs[1]) || mxIsComplex(prhs[1]))
    mexErrMsgTxt("The second input must be a matrix of real (double) values corresponding to points values."); 

  // First output
  btk::Acquisition::Pointer acq = btk_MOH_get_object<btk::Acquisition>(prhs[0]);

  int numberOfValuesPerPoint = acq->GetPointFrameNumber() * 3;
  int numberOfPoints = acq->GetPointNumber();

  if (mxGetNumberOfElements(prhs[1]) != numberOfPoints*numberOfValuesPerPoint)
    mexErrMsgTxt("The second input doesn't have the same size than the number of points values.");
    
  double* values = mxGetPr(prhs[1]);

  int i = 0;
  int j = numberOfValuesPerPoint;
  double* v = 0;
  btk::Acquisition::PointIterator it = acq->BeginPoint();
  while (i < numberOfPoints * numberOfValuesPerPoint)
  {
    if (j >= numberOfValuesPerPoint)
    {
      v = (*it)->GetValues().data();
      ++it;
      j = 0;
    }
    v[j] = values[i];
    v[j+1] = values[i+1];
    v[j+2] = values[i+2];
    i+=3; j+=3;
  }
};


