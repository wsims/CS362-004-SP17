/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
       UrlValidator validator = new UrlValidator();
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       //These should all return true
	   if (!urlVal.isValid("http://www.amazon.com")) {
	       System.out.println("http://www.amazon.com - Error expected true");
       }
       if (!urlVal.isValid("http://amazon.com")) {
           System.out.println("http://amazon.com - Error expected true");
       }
       if (!urlVal.isValid("http://amazon.com/shouldpass")) {
           System.out.println("http://amazon.com/shouldpass - Error expected true");
       }
       if (!urlVal.isValid("http://amazon.com/should/pass")) {
           System.out.println("http://amazon.com/should/pass - Error expected true");
       }
       if (!urlVal.isValid("http://255.255.255.255")) {
           System.out.println("http://255.255.255.255 - Error expected true");
       }


       //These should all return false
       if (urlVal.isValid("://www.amazon.com")) {
           System.out.println("://www.amazon.com -  Error expected false");
       }
       if (urlVal.isValid("http:/www.amazon.com")) {
           System.out.println("http:/www.amazon.com - Error expected false");
       }
       if (urlVal.isValid("http://www.amazon")) {
           System.out.println("http://www.amazon - Error expected false");
       }
       if (urlVal.isValid("abc://www.amazon.com")) {
           System.out.println("abc://www.amazon.com - Error expected false"); //BUG returns true despite invalid URL Scheme
       }
       if (urlVal.isValid("http//www.amazon.com")) {
           System.out.println("http//www.amazon.com - Error expected false");
       }
       if (urlVal.isValid("")) {
           System.out.println("Empty url - Error expected false");
       }
       if (urlVal.isValid("ajka;kjnsg;kjna")) {
           System.out.println("ajka;kjnsg;kjna - Error expected false");
       }
       if (urlVal.isValid("http://666.666.666.666")) {
           System.out.println("http://666.666.666.666 - Error expected false"); //BUG returns true, but address is too large
       }
   }
   
   
   public void testSchemePartition()
   {
	   
   }
   
   public void testAuthorityPartition()
   {
	   
   }

   public void testPortPartition()
   {

   }

   public void testPathPartition()
   {

   }

   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
