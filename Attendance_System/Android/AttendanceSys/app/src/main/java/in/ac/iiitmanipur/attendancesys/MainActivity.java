package in.ac.iiitmanipur.attendancesys;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.google.android.gms.auth.api.Auth;
import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInResult;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.SignInButton;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.common.api.Status;

public class MainActivity extends AppCompatActivity implements View.OnClickListener,GoogleApiClient.OnConnectionFailedListener {
    private LinearLayout Prof_Section;

    //----------------Google Signin------------
    private LinearLayout SignIn_Sec;
    protected Button SignOut;
    private TextView Name, Email;
    private ImageView Prof_Pic;
    private GoogleApiClient googleApiClient;
    private static final int Req_code = 9001;
    //-------------------------------------------

    @SuppressLint("WrongViewCast")
    @Override
    protected void onCreate(Bundle savedInstanceState){
    super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Prof_Section = (LinearLayout)findViewById(R.id.Prof_section);
        SignIn_Sec = (LinearLayout)findViewById(R.id.SignIn_sec);
        SignOut = (Button)findViewById(R.id.g_signout);
        SignInButton signIn = (SignInButton) findViewById(R.id.g_login);
        Name =(TextView)findViewById(R.id.name);
        Email = (TextView)findViewById(R.id.email);
        Prof_Pic = (ImageView)findViewById(R.id.image_view);
        signIn.setOnClickListener(this);
        SignOut.setOnClickListener(this);
        @SuppressLint("RestrictedApi") GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(this);
        updateUI(account);

        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestEmail()
                .build();
        googleApiClient = new GoogleApiClient.Builder(this).enableAutoManage(this,this).addApi(Auth.GOOGLE_SIGN_IN_API,gso).build();
    }
    @Override

    //----------------Google Signin------------
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.g_login:
                signIn();
                break;
            case R.id.g_signout:
                SignOut();
                break;
        }

    }
    @Override
    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {

    }
    private void signIn(){
        Intent intent = Auth.GoogleSignInApi.getSignInIntent(googleApiClient);
        startActivityForResult(intent, Req_code);

    }
    private void SignOut(){
        Auth.GoogleSignInApi.signOut(googleApiClient).setResultCallback(new ResultCallback<Status>() {
            @Override
            public void onResult(@NonNull Status status) {
                updateUI(false);
            }
        });

    }
    private void handleResult(GoogleSignInResult result){
        if(result.isSuccess()){
            GoogleSignInAccount account = result.getSignInAccount();
            String name = account.getDisplayName();
            String email = account.getEmail();
            String img_url = account.getPhotoUrl().toString();
            Name.setText(name);
            Email.setText(email);
            Glide.with(this).load(img_url).into(Prof_Pic);

            Boolean suffix = email.contains("iiitmanipur.ac.in");
            if(suffix)
                updateUI(true);
            else {
                Toast.makeText(MainActivity.this, "Please Sign in using @iiitmanipur.ac.in", Toast.LENGTH_LONG).show();
                SignOut();
                updateUI(false);
            }
        }

    }
    private void updateUI(boolean isLogin){
        if(isLogin){
            Prof_Section.setVisibility(View.VISIBLE);
            SignIn_Sec.setVisibility(View.GONE);
        }
        else{
            Prof_Section.setVisibility(View.GONE);
            SignIn_Sec.setVisibility(View.VISIBLE);
        }

    }
    private void updateUI(GoogleSignInAccount isLogin){
        if(isLogin!=null){
            String name = isLogin.getDisplayName();
            String email = isLogin.getEmail();
            String img_url = isLogin.getPhotoUrl().toString();
            Name.setText(name);
            Email.setText(email);
            Glide.with(this).load(img_url).into(Prof_Pic);
            Prof_Section.setVisibility(View.VISIBLE);
            SignIn_Sec.setVisibility(View.GONE);
        }
        else{
            Prof_Section.setVisibility(View.GONE);
            SignIn_Sec.setVisibility(View.VISIBLE);
        }

    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        super.onActivityResult(requestCode, resultCode, data);

        if(requestCode == Req_code){
            GoogleSignInResult result = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
            handleResult(result);
        }
    }
    //-------------------------------------------

    //-----------------Multiscreen operation------------
    public void openSem1(View view){
        Intent i = new Intent(this, SubjectActivity.class);
        startActivity(i);
    }
    //-------------------------------------------

}
