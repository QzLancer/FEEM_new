/*
+--------------------------------------------------------------------+
| Color.h                                                            |
+--------------------------------------------------------------------+
|                                                                    |
| Author : Alfredo Ferreira                                          |
| E-mail : alfredo.ferreira@inesc-id.pt                              |
| Website: http://immi.inesc-id.pt/~afj                              |
|                                                                    |
| Version: 1.00                                                      |
| Created: Nov 2007                                                  |
|                                                                    |
+--------------------------------------------------------------------+
| Intelligent Multimodal Interfaces Group                            |
| Department of Information Systems and Computer Science             |
| INESC-ID/IST/Technical University of Lisbon                        |
| Taguspark, Edificio IST, Nucleo 9, Piso 2                          |
| 2744-016 Porto Salvo, Portugal                                     |
|                                                                    |
| Tel: +351.21.4233512, Fax: +351.21.4233290                         |
+--------------------------------------------------------------------+
|                                                                    |
| Copyright (c) 2007 INESC-ID                                        |
|                                                                    |
|   The copyright to the computer program(s) herein is the property  |
| of INESC-ID, Portugal. The program(s) may be used and/or copied    |
| only with the written permission of INESC-ID or in accordance with |
| the terms and conditions stipulated in the agreement/contract      |
| under which the program(s) have been supplied.                     |
|                                                                    |
+--------------------------------------------------------------------+
*/

#pragma once

#include <string>

class Color
{
public:
	//Color(void);
	//~Color(void);

	static void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v );
	static void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v );

	static std::string RGBtoHEX(float r, float g, float b);
};
