<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Crypt;
use Illuminate\Support\Facades\DB;

class registration_controller extends Controller
{

    function registration(Request $request){
        $name =     strip_tags(trim($request->input('name')));
        $email =    strip_tags(trim($request->input('email')));
        
        $password = strip_tags(trim($request->input('password')));
        $encrypted_password = Crypt::encrypt($password); //encrypted password

        $getCount = DB::table('users')->where('email', $email)->count(); //getting user count
        
        if($name == '') return 'Name required';
        else if($email == '') return 'Email required';
        else if($password == '') return 'Password required';
        else if($getCount != 0 ) return "User exists";

        else
           $result = DB::table('users')->insert([
                'name' => $name,
                'email' => $email,
                'password' => $encrypted_password,
            ]);

            if($result) return "Successful";
            else return "Failed";
    } 

}
