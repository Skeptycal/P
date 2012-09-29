/*
Copyright (c) 2012, Andrew Carter, Dietrich Langenbach, Xanda Schofield
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.
*/
#ifndef WRAPPER_OINDENTSTREAM
#define WRAPPER_OINDENTSTREAM
#include <string>
#include <iostream>
namespace wrapper
{
    struct Endl {} endl;
    
    class oIndentStream
    {
        size_t indents_;
        size_t precedent_;
        std::string holding_;
        std::ostream* wrapped_;
        bool newline_;
    public:
        oIndentStream(std::ostream& wrapped)
            : indents_(0), precedent_(0),
                wrapped_(&wrapped), newline_(true) {}
        
        oIndentStream& operator++()
        {
            ++indents_;
            return *this;
        }
        
        oIndentStream& operator--()
        {
            if(indents_ != 0)
                --indents_;
            return *this;
        }
        
        size_t& operator*() { return precedent_; }
        const size_t& operator*() const { return precedent_; }
        
        oIndentStream& operator<<(const Endl&)
        {
            newline_ = true;
            *wrapped_ << std::endl;
            return *this;
        }
        
        oIndentStream& operator<<(const std::string& s)
        {
            if(newline_)
                for(size_t i = 0; i < indents_; ++i)
                    *wrapped_ << "    ";
            newline_ = false;
            *wrapped_ << s;
            return *this;
        }
        
        oIndentStream& operator<<(const unsigned long long int& ui)
        {
            if(newline_)
                for(size_t i = 0; i < indents_; ++i)
                    *wrapped_ << "    ";
            newline_ = false;
            *wrapped_ << ui;
            return *this;
        }
    };
}
#endif