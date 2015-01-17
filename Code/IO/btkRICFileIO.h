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

#ifndef __btkRICFileIO_h
#define __btkRICFileIO_h

#include "btkAcquisitionFileIO.h"
#include "btkException.h"

namespace btk
{
  class RICFileIOException : public Exception
  {
  public:
    explicit RICFileIOException(const std::string& msg)
    : Exception(msg)
    {};
      
    virtual ~RICFileIOException() throw() {};
  };
  
  class RICFileIO : public AcquisitionFileIO
  {
    BTK_FILE_IO_SUPPORTED_EXTENSIONS(Extension("RIC") | Extension("RIF"));
    BTK_FILE_IO_ONLY_READ_OPERATION;
    
  public:
    typedef btkSharedPtr<RICFileIO> Pointer;
    typedef btkSharedPtr<const RICFileIO> ConstPointer;
    
    static Pointer New() {return Pointer(new RICFileIO());};
    
    // ~RICFileIO(); // Implicit.
    
    BTK_IO_EXPORT virtual bool CanReadFile(const std::string& filename);
    BTK_IO_EXPORT virtual void Read(const std::string& filename, Acquisition::Pointer output);
    
  protected:
    BTK_IO_EXPORT RICFileIO();
    
  private:
    RICFileIO(const RICFileIO& ); // Not implemented.
    RICFileIO& operator=(const RICFileIO& ); // Not implemented. 
   };
};

#endif // __btkRICFileIO_h
