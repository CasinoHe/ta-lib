/* TA-LIB Copyright (c) 1999-2003, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  JP       John Price <jp_talib@gcfl.net>
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  070203 JP   Initial.
 *
 */

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */    #using <mscorlib.dll>
/* Generated */    #include "Core.h"
/* Generated */    namespace TA { namespace Lib {
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_UTILITY_H
/* Generated */    #include "ta_utility.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_MEMORY_H
/* Generated */    #include "ta_memory.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #define TA_PREFIX(x) TA_##x
/* Generated */ #define INPUT_TYPE   double
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ int Core::LINEARREG_INTERCEPT_Lookback( int           optInTimePeriod_0 )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ int TA_LINEARREG_INTERCEPT_Lookback( int           optInTimePeriod_0 )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert lookback code here. */
   return optInTimePeriod_0-1;
}

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/*
 * TA_LINEARREG_INTERCEPT - Linear Regression Intercept
 * 
 * Input  = double
 * Output = double
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod_0:(From 2 to 100000)
 *    Number of period
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::LINEARREG_INTERCEPT( int    startIdx,
/* Generated */                                                  int    endIdx,
/* Generated */                                                  double       inReal_0 __gc [],
/* Generated */                                                  int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                                                  [OutAttribute]Int32 *outBegIdx,
/* Generated */                                                  [OutAttribute]Int32 *outNbElement,
/* Generated */                                                  double        outReal_0 __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_LINEARREG_INTERCEPT( int    startIdx,
/* Generated */                                    int    endIdx,
/* Generated */                                    const double inReal_0[],
/* Generated */                                    int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                                    int          *outBegIdx,
/* Generated */                                    int          *outNbElement,
/* Generated */                                    double        outReal_0[] )
/* Generated */ #endif
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
{
	/* insert local variable here */
   int outIdx;

   int today, lookbackTotal;
   double SumX, SumXY, SumY, SumXSqr, Divisor;

   double m;
   int i;

   double tempValue1;

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */ 
/* Generated */    /* Validate the parameters. */
/* Generated */    if( !inReal_0 ) return TA_BAD_PARAM;
/* Generated */    /* min/max are checked for optInTimePeriod_0. */
/* Generated */    if( (int)optInTimePeriod_0 == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod_0 = 14;
/* Generated */    else if( ((int)optInTimePeriod_0 < 2) || ((int)optInTimePeriod_0 > 100000) )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */    if( outReal_0 == NULL )
/* Generated */       return TA_BAD_PARAM;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* Linear Regression is a concept also known as the
    * "least squares method" or "best fit." Linear
    * Regression attempts to fit a straight line between
    * several data points in such a way that distance
    * between each data point and the line is minimized.
    *
    * For each point, a straight line over the specified
    * previous bar period is determined in terms
    * of y = b + m*x:
    *
    * TA_LINEARREG          : Returns b+m*(period-1)
    * TA_LINEARREG_SLOPE    : Returns 'm'
    * TA_LINEARREG_ANGLE    : Returns 'm' in degree.
    * TA_LINEARREG_INTERCEPT: Returns 'b'
    * TA_TSF                : Returns b+m*(period)
    */

   /* Adjust startIdx to account for the lookback period. */
   lookbackTotal = TA_LINEARREG_Lookback( optInTimePeriod_0 );

   if( startIdx < lookbackTotal )
      startIdx = lookbackTotal;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      *outBegIdx    = 0;
      *outNbElement = 0;
      return TA_SUCCESS;
   }

   outIdx = 0; /* Index into the output. */
   today = startIdx;

   SumX = optInTimePeriod_0 * ( optInTimePeriod_0 - 1 ) * 0.5;
   SumXSqr = optInTimePeriod_0 * ( optInTimePeriod_0 - 1 ) * ( 2 * optInTimePeriod_0 - 1 ) / 6;
   Divisor = SumX * SumX - optInTimePeriod_0 * SumXSqr;

   while( today <= endIdx )
   {
     SumXY = 0;
     SumY = 0;
     for( i = optInTimePeriod_0; i--; )
     {
       SumY += tempValue1 = inReal_0[today - i];
       SumXY += (double)i * tempValue1;
     }
     m = ( optInTimePeriod_0 * SumXY - SumX * SumY) / Divisor;     
     outReal_0[outIdx++] = ( SumY - m * SumX ) / (double)optInTimePeriod_0;
     today++;
   }

   *outBegIdx = startIdx;
   *outNbElement = outIdx;

   return TA_SUCCESS;
}

/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #if !defined( _MANAGED )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED )
/* Generated */ enum Core::TA_RetCode Core::LINEARREG_INTERCEPT( int    startIdx,
/* Generated */                                                  int    endIdx,
/* Generated */                                                  float        inReal_0 __gc [],
/* Generated */                                                  int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                                                  [OutAttribute]Int32 *outBegIdx,
/* Generated */                                                  [OutAttribute]Int32 *outNbElement,
/* Generated */                                                  double        outReal_0 __gc [] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_LINEARREG_INTERCEPT( int    startIdx,
/* Generated */                                      int    endIdx,
/* Generated */                                      const float  inReal_0[],
/* Generated */                                      int           optInTimePeriod_0, /* From 2 to 100000 */
/* Generated */                                      int          *outBegIdx,
/* Generated */                                      int          *outNbElement,
/* Generated */                                      double        outReal_0[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    int outIdx;
/* Generated */    int today, lookbackTotal;
/* Generated */    double SumX, SumXY, SumY, SumXSqr, Divisor;
/* Generated */    double m;
/* Generated */    int i;
/* Generated */    double tempValue1;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return TA_OUT_OF_RANGE_START_INDEX;
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return TA_OUT_OF_RANGE_END_INDEX;
/* Generated */     if( !inReal_0 ) return TA_BAD_PARAM;
/* Generated */     if( (int)optInTimePeriod_0 == TA_INTEGER_DEFAULT )
/* Generated */        optInTimePeriod_0 = 14;
/* Generated */     else if( ((int)optInTimePeriod_0 < 2) || ((int)optInTimePeriod_0 > 100000) )
/* Generated */        return TA_BAD_PARAM;
/* Generated */     if( outReal_0 == NULL )
/* Generated */        return TA_BAD_PARAM;
/* Generated */  #endif 
/* Generated */    lookbackTotal = TA_LINEARREG_Lookback( optInTimePeriod_0 );
/* Generated */    if( startIdx < lookbackTotal )
/* Generated */       startIdx = lookbackTotal;
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       *outBegIdx    = 0;
/* Generated */       *outNbElement = 0;
/* Generated */       return TA_SUCCESS;
/* Generated */    }
/* Generated */    outIdx = 0; 
/* Generated */    today = startIdx;
/* Generated */    SumX = optInTimePeriod_0 * ( optInTimePeriod_0 - 1 ) * 0.5;
/* Generated */    SumXSqr = optInTimePeriod_0 * ( optInTimePeriod_0 - 1 ) * ( 2 * optInTimePeriod_0 - 1 ) / 6;
/* Generated */    Divisor = SumX * SumX - optInTimePeriod_0 * SumXSqr;
/* Generated */    while( today <= endIdx )
/* Generated */    {
/* Generated */      SumXY = 0;
/* Generated */      SumY = 0;
/* Generated */      for( i = optInTimePeriod_0; i--; )
/* Generated */      {
/* Generated */        SumY += tempValue1 = inReal_0[today - i];
/* Generated */        SumXY += (double)i * tempValue1;
/* Generated */      }
/* Generated */      m = ( optInTimePeriod_0 * SumXY - SumX * SumY) / Divisor;     
/* Generated */      outReal_0[outIdx++] = ( SumY - m * SumX ) / (double)optInTimePeriod_0;
/* Generated */      today++;
/* Generated */    }
/* Generated */    *outBegIdx = startIdx;
/* Generated */    *outNbElement = outIdx;
/* Generated */    return TA_SUCCESS;
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }} // Close namespace TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

