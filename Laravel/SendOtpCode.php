<?php

namespace App\Http\Controllers\Auth;

use App\Http\Controllers\Controller;
use Illuminate\Http\Request;
use SoapClient;

class SendOtpCode extends Controller
{
    function checkOtpInSession(Request $request){
        //$request->session()->flush();
        $hasOtp    = $request->session()->get('otp');
        $hasNumber = $request->session()->get('customerNumber');
        return response()->json(['otp'=>$hasOtp, 'customerNumber'=> $hasNumber]);
    }

    //SendVerificationCode
    function sendOtpCode(Request $request){
        $customerNumber   = strip_tags(trim($request->input('customer_number')));
        $verificationCode = strip_tags(trim($request->input('verification_code')));
        $message          = 'প্রিয় গ্রাহক, আপনার ভেরিফিকেশন কোড: '. $verificationCode;

        $request->session()->put('otp', $verificationCode);
        $request->session()->put('customerNumber', $customerNumber);

        try{
            $soapClient = new SoapClient("https://api2.onnorokomSMS.com/sendSMS.asmx?wsdl");
            $paramArray = array(
            'apiKey' => "db1f11bc-a3f3-4b3b-a57c-dfc19ced74fe",
            'messageText' => $message,
            'numberList' =>  $customerNumber,
            'smsType' => "TEXT",
            'maskName' => '',
            'campaignName' => 'Verification',
            );
            $value = $soapClient->__call("NumberSms", array($paramArray));
            
            return response()->json([$value->NumberSmsResult]);
        }
        catch (Exception $e) {
            return $e->getMessage();
        }

        return $verificationCode;
    }
}
