#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#****************************************************************************************************************************************************
# Copyright 2017 NXP
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    * Redistributions of source code must retain the above copyright notice,
#      this list of conditions and the following disclaimer.
#
#    * Redistributions in binary form must reproduce the above copyright notice,
#      this list of conditions and the following disclaimer in the documentation
#      and/or other materials provided with the distribution.
#
#    * Neither the name of the NXP. nor the names of
#      its contributors may be used to endorse or promote products derived from
#      this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#****************************************************************************************************************************************************

import os
import sys

def CheckVersion():
    # type: () -> None
    forceAllowPythonVersion = False
    if (sys.version_info >= (3, 4) and sys.version_info < (3, 5)):
        try:
            from typing import Any
            forceAllowPythonVersion = True
        except ImportError:
            if os.name == 'posix':
                print("To run this tool with Python 3.4 please install the 'typing' library with 'sudo pip3 install typing' or upgrade to Python 3.5+. If you dont have 'pip3' then you need to install it with 'sudo apt-get install python3-pip'")
            elif os.name == 'nt':
                print("To run this tool with Python 3.4 please install the 'typing' library with 'python3 -m pip install typing' or upgrade to Python 3.5+.")
            else:
                print("To run this tool with Python 3.4 please install the 'typing' library or upgrade to Python 3.5+.")
            sys.exit(1)

    if not forceAllowPythonVersion and sys.version_info < (3, 4):
        print("This tool requires Python 3.4 or better, please upgrade your python version. You are running python {0}.{1}.{2}".format(sys.version_info[0], sys.version_info[1], sys.version_info[2]))
        # So exit with a error
        sys.exit(1)
