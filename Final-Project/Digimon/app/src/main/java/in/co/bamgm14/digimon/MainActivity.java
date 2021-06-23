package in.co.bamgm14.digimon;

import androidx.appcompat.app.AppCompatActivity;

import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import in.co.bamgm14.digimon.data.DownloadSpriteCallback;
import in.co.bamgm14.digimon.data.DownloadSpriteTask;
import in.co.bamgm14.digimon.data.Response;
import in.co.bamgm14.digimon.data.Sender;
import in.co.bamgm14.digimon.data.SenderCallback;

public class MainActivity extends AppCompatActivity implements DownloadSpriteCallback, SenderCallback {
    public TextView digimon_name;
    public TextView digimon_type;
    public TextView digimon_stage;
    public TextView digimon_experience;
    public TextView digi_msg;
    public TextView digimon_bond;

    public String code;

    public ImageView digimon_img;

    private SharedPreferences preferences;
    private SharedPreferences.Editor editor;

    private DownloadSpriteTask downloadSpriteTask;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        preferences = PreferenceManager.getDefaultSharedPreferences(this);
        editor = preferences.edit();
        code = preferences.getString("code", Response.CODE_NONE);

        downloadSpriteTask = new DownloadSpriteTask(this);

        Log.d("cs50", code);

        setContentView(R.layout.activity_main);
        digimon_name = findViewById(R.id.digimon_name);
        digimon_type = findViewById(R.id.digimon_type);
        digimon_stage = findViewById(R.id.digimon_stage);
        digimon_experience = findViewById(R.id.digimon_experience);
        digi_msg = findViewById(R.id.digi_msg);
        digimon_img = findViewById(R.id.digimon_img);
        digimon_bond = findViewById(R.id.digimon_bond);
        new Sender(this).execute(DigiFaceConstants.NONE);
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
            Log.d("cs50", "Begin!");
            new Sender(this).execute(DigiFaceConstants.REGISTER);
            Log.d("cs50", "Done!");
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putString("code", code);
        editor.putString("code", code);
        editor.apply();
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        code = preferences.getString("code", Response.CODE_NONE);
        new Sender(this).execute(DigiFaceConstants.NONE);
    }

    @Override
    public void onDownloadImage(Bitmap bitmap) {
        // If the api callback happens after the activity is closed, cancel response handling
        if (!isFinishing()) {
            return;
        }

        // Render digimon image once downloaded
        digimon_img.setImageBitmap(bitmap);
    }

    @Override
    public void onSend(Response response, Digimon digimon) {
        // If the api callback happens after the activity is closed, cancel response handling
        if (!isFinishing()) {
            return;
        }

        if (digimon != null) {
            // Render Digimon stats view
            digimon_name.setText(String.format("Name:%s", digimon.getName()));
            digimon_type.setText(String.format("Type:%s", digimon.getType()));
            digimon_stage.setText(String.format("Stage:%s", digimon.getStage()));
            digimon_experience.setText(String.format("Experience:%s", digimon.getExperience().toString()));
            digimon_bond.setText(String.format("Bond:%s", digimon.getBond().toString()));

            // Start task to download digimon image
            downloadSpriteTask.execute(digimon.getImageUrl());
        }

        if (response != null) {
            // Set response - message and code
            digi_msg.setText(response.getMessage());
            editor.putString("code", response.getCode());
            editor.apply();
        }
    }

    public void PVE(View view) {
        new Sender(this).execute(DigiFaceConstants.PVE);
    }

    public void Play(View view) {
        new Sender(this).execute(DigiFaceConstants.PLAY);
    }

    public void Digivolve(View view) {
        new Sender(this).execute(DigiFaceConstants.DIGIVOLVE);
    }

}