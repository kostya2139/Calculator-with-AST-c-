package com.example.my;

public class InformationFromC {
    public String result, exception;

    public void setBoth(String _result, String _exception)
    {
        result = _result;
        exception = _exception;
    }

    public InformationFromC() {
        result = "";
        exception = "";
    }
}
