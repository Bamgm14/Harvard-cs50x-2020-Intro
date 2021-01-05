package in.co.bamgm14.digimon;

import androidx.appcompat.app.AppCompatActivity;

import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Message;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.JSONObject;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.URL;

public class MainActivity extends AppCompatActivity {
    public TextView digimon_name;
    public TextView digimon_type;
    public TextView digimon_stage;
    public TextView digimon_experience;
    public TextView digi_msg;
    public TextView digimon_bond;

    public String code;

    public ImageView digimon_img;
    public JSONObject Digimon;
    public Interface Digiface = new Interface();
    public String message;

    private SharedPreferences preferences;
    private SharedPreferences.Editor editor;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        preferences = PreferenceManager.getDefaultSharedPreferences(this);
        editor = preferences.edit();
        code = preferences.getString("code","None");

        Log.d("cs50",code);

        setContentView(R.layout.activity_main);
        digimon_name = findViewById(R.id.digimon_name);
        digimon_type = findViewById(R.id.digimon_type);
        digimon_stage = findViewById(R.id.digimon_stage);
        digimon_experience = findViewById(R.id.digimon_experience);
        digi_msg = findViewById(R.id.digi_msg);
        digimon_img = findViewById(R.id.digimon_img);
        digimon_bond = findViewById(R.id.digimon_bond);
        new Sender().execute(-1);
    }
    @Override
    protected void onResume() {
        super.onResume();
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            Log.d("cs50","Begin!");
            new Sender().execute(0);
            Log.d("cs50","Done!");
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public class Sender extends AsyncTask<Integer, Void, Void> {
        @Override
        protected Void doInBackground(Integer... ints) {
            for (int x = 0; x < ints.length; x++) {
                Socket s = null;
                message = "";
                Log.d("cs50", "A");
                try {
                    s = new Socket("4.tcp.ngrok.io", 12220);
                    Log.d("cs50", "A");
                    DataInputStream din = new DataInputStream(s.getInputStream());
                    Log.d("cs50", "A");
                    DataOutputStream dout = new DataOutputStream(s.getOutputStream());
                    dout.writeUTF(code);
                    dout.flush();
                    Log.d("cs50",din.readUTF());
                    if (ints[x].intValue() == Digiface.REGISTER) {
                        dout.writeUTF("Register");
                        dout.flush();
                        code = (String) din.readUTF().subSequence(0,1);
                    }
                    if (ints[x].intValue() == Digiface.PLAY) {
                        dout.writeUTF("Play");
                        dout.flush();
                        message = din.readUTF();
                    }
                    if (ints[x].intValue() == Digiface.PVE) {
                        dout.writeUTF("PVE");
                        dout.flush();
                        message = din.readUTF();
                    }
                    if (ints[x].intValue() == Digiface.DIGIVOLVE) {
                        dout.writeUTF("Digivolve");
                        dout.flush();
                        message = din.readUTF();
                    }
                    Log.d("cs50",code);
                    dout.writeUTF(code);
                    String Word = din.readUTF();
                    JSONObject json = new JSONObject(Word);
                    Log.d("cs50", json.toString());
                    s.close();
                    Digimon = json;
                    editor.putString("code",code);
                    editor.apply();
                    return null;
                } catch (Exception e) {
                    Log.e("cs50[Send]", e.toString());
                    Digimon = null;
                    return null;
                }
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void aVoid) {
            editor.putString("code",code);
            editor.apply();
            try{
                if (Digimon != null) {
                    digimon_name.setText("Name:" + Digimon.getString("name"));
                    digimon_type.setText("Type:" + Digimon.getString("type"));
                    digimon_stage.setText("Stage:" + Digimon.getString("stage"));
                    digimon_experience.setText("Experience:" + String.valueOf(Digimon.getDouble("experience")));
                    digi_msg.setText(message);
                    digimon_bond.setText(String.valueOf("Bond:" + Digimon.getDouble("bond")));
                    new DownloadSpriteTask().execute(Digimon.getString("url"));
                }
            }
            catch (Exception e){
                Log.e("cs50[Put]",e.toString());
            }
            super.onPostExecute(aVoid);
        }
    }
    @Override
    protected void onSaveInstanceState(Bundle savedInstanceState){
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putString("code",code);
        editor.putString("code",code);
        editor.apply();
    }
    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        code = preferences.getString("code","None");
        new Sender().execute(-1);
    }
    public void PVE(View view){ new Sender().execute(Digiface.PVE); }
    public void Play(View view){ new Sender().execute(Digiface.PLAY); }
    public void Digivolve(View view) {new Sender().execute(Digiface.DIGIVOLVE);}
    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                return BitmapFactory.decodeStream(url.openStream());
            } catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }
        @Override
        protected void onPostExecute(Bitmap bitmap) {
            digimon_img.setImageBitmap(bitmap);
        }
    }
}