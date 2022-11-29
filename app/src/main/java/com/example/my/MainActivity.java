package com.example.my;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.TypedValue;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    public InformationFromC answer;
    static {
        System.loadLibrary("my");
    }

    private native void calculate(String s);

    @SuppressLint("ResourceAsColor")
    private void setException(TextView res, boolean flag) {
        if(flag) {
            res.setTextColor(getResources().getColor(R.color.red));
            res.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 50);
        }
        else {
            res.setTextColor(getResources().getColor(R.color.white));
            res.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 26);
        }
    }
    private boolean is_operation(char c)
    {
        return c=='+' || c=='-' || c=='*' || c=='/';
    }
    private boolean is_dig(char c)
    {
        return c>'0' && c<'9';
    }
    private boolean is_bracket(char c)
    {
        return c=='(' || c==')';
    }
    boolean isException = false, firstZero = false, already_dot = false;
    int difference = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        answer = new InformationFromC();
        setContentView(R.layout.activity_main);
        TextView res = findViewById(R.id.textView);
        findViewById(R.id.one).setOnClickListener(view -> {
            if(isException || firstZero) {
                setException(res, false);
                res.setText("1");
                isException = firstZero = false;
            }
            else res.append("1");
        });
        findViewById(R.id.two).setOnClickListener(view -> {
            if(isException || firstZero) {
                setException(res, false);
                res.setText("2");
                isException = firstZero = false;
            }
            else res.append("2");
        });
        findViewById(R.id.three).setOnClickListener(view -> {
            if(isException || firstZero) {
                setException(res, false);
                res.setText("3");
                isException = firstZero = false;
            }
            else res.append("3");
        });
        findViewById(R.id.four).setOnClickListener(view -> {
            if(isException || firstZero) {
                setException(res, false);
                res.setText("4");
                isException = firstZero = false;
            }
            else res.append("4");
        });
        findViewById(R.id.five).setOnClickListener(view -> {
            if(isException || firstZero) {
                setException(res, false);
                res.setText("5");
                isException = firstZero = false;
            }
            else res.append("5");
        });
        findViewById(R.id.six).setOnClickListener(view -> {
            if(isException || firstZero) {
                setException(res, false);
                res.setText("6");
                isException = firstZero = false;
            }
            else res.append("6");
        });
        findViewById(R.id.seven).setOnClickListener(view -> {
            if(isException || firstZero) {
                setException(res, false);
                res.setText("7");
                isException = firstZero = false;
            }
            else res.append("7");
        });
        findViewById(R.id.eight).setOnClickListener(view -> {
            if(isException || firstZero) {
                setException(res, false);
                res.setText("8");
                isException = firstZero = false;
            }
            else res.append("8");
        });
        findViewById(R.id.nine).setOnClickListener(view -> {
            if(isException || firstZero) {
                setException(res, false);
                res.setText("9");
                isException = firstZero = false;
            }
            else res.append("9");
        });
        findViewById(R.id.zero).setOnClickListener(view -> {
            if(isException) {
                setException(res, false);
                res.setText("0");
                isException = false;
                firstZero = true;
            }
            if(!firstZero) {
                String s = res.getText().toString();
                if(s.length() == 0  || is_operation(s.charAt(s.length()-1))) firstZero = true;
                res.append("0");
            }
        });
        findViewById(R.id.dot).setOnClickListener(view -> {
            if(isException) {
                setException(res, false);
                res.setText(".");
                isException = firstZero = false;
                already_dot = true;
            }
            else if(!already_dot) {
                res.append(".");
                firstZero = false;
                already_dot = true;
            }
        });
        findViewById(R.id.AC).setOnClickListener(view -> {
            setException(res, false);
            isException = firstZero = already_dot = false;
            difference = 0;
            res.setText("");
        });
        findViewById(R.id.minus).setOnClickListener(view -> {
            if(isException) {
                setException(res, false);
                res.setText("-");
                isException = firstZero = already_dot = false;
            }
            else {
                String s = res.getText().toString();
                if(!(s.length() > 0 && s.charAt(s.length()-1) == '-')) {
                    res.append("-");
                    firstZero = already_dot = false;
                }
            }
        });
        findViewById(R.id.plus).setOnClickListener(view -> {
            if(!isException) {
                String s = res.getText().toString();
                if(s.length()>0 && !is_operation(s.charAt(s.length()-1))) {
                    res.append("+");
                    firstZero = already_dot = false;
                }
            }
        });
        findViewById(R.id.mul).setOnClickListener(view -> {
            if(!isException) {
                String s = res.getText().toString();
                if(s.length()>0 && !is_operation(s.charAt(s.length()-1))) {
                    res.append("*");
                    firstZero = already_dot = false;
                }
            }
        });
        findViewById(R.id.div).setOnClickListener(view -> {
            if(!isException) {
                String s = res.getText().toString();
                if(s.length()>0 && !is_operation(s.charAt(s.length()-1))) {
                    res.append("/");
                    firstZero = already_dot = false;
                }
            }
        });
        findViewById(R.id.open).setOnClickListener(view -> {
            if(isException) {
                setException(res, false);
                res.setText("(");
                isException = firstZero = already_dot = false;
            }
            else {
                String s = res.getText().toString();
                if(s.length() == 0 || is_operation(s.charAt(s.length()-1))) {
                    res.append("(");
                    ++difference;
                }
            }
        });
        findViewById(R.id.close).setOnClickListener(view -> {
            if(!isException && difference > 0) {
                String s = res.getText().toString();
                if(s.charAt(s.length()-1) <'9' && s.charAt(s.length()-1) >'0' || s.charAt(s.length()-1) == '.') {
                    --difference;
                    res.append(")");
                }
            }
        });
        findViewById(R.id.C).setOnClickListener(view -> {
            if(isException) {
                setException(res, false);
                isException = firstZero = already_dot = false;
                res.setText("");
            }
            else {
                String s = res.getText().toString();
                if(s.length() > 0) {
                    if(s.charAt(s.length()-1) == '.') already_dot = false;
                    if(s.charAt(s.length()-1) == '(') --difference;
                    if(s.charAt(s.length()-1) == ')') ++difference;
                    if(s.charAt(s.length()-1) == '0' && (s.length() == 1 || is_dig(s.charAt(s.length()-2)) || s.charAt(s.length()-2) == '.')) firstZero = false;
                    if(is_operation(s.charAt(s.length()-1)) && s.length() > 1 && !is_operation(s.charAt(s.length()-2)) && !is_bracket(s.charAt(s.length()-2)))
                    {
                        if(s.charAt(s.length()-2) == '0' && (s.length() == 2 || is_operation(s.charAt(s.length()-3)) || is_bracket(s.charAt(s.length()-3))))
                            firstZero = true;
                        int i = s.length()-2;
                        while(i >= 0 && is_dig(s.charAt(i)))
                            --i;
                        if(i >= 0 && s.charAt(i) == '.') already_dot = true;
                    }
                    res.setText(s.substring(0, s.length()-1));
                }
            }
        });
        findViewById(R.id.calc).setOnClickListener(view -> {
            if (!isException) {
                difference=0;
                calculate(res.getText().toString());
                if (!answer.exception.equals("")) {
                    setException(res, true);
                    isException = true;
                    already_dot = false;
                    firstZero = false;
                    res.setText(answer.exception);
                }
                else {
                    if(answer.result.equals("0")) firstZero = true;
                    else firstZero = false;
                    if(answer.result.contains(".") || answer.result.contains("e")) already_dot = true;
                    else already_dot = false;
                    res.setText(answer.result);
                }
            }
        });
    }
}