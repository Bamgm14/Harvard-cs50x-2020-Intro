package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;
import java.util.ListIterator;

public class PokemonActivity extends AppCompatActivity {
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private TextView caughtTextView;
    private TextView desc;
    private ImageView pixelmon;
    private Button catching;
    private String url;
    private RequestQueue requestQueue;
    private Pokemon poke;
    private Boolean caught;

    private SharedPreferences preferences;
    private SharedPreferences.Editor editor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);
        requestQueue = Volley.newRequestQueue(getApplicationContext());
        url = getIntent().getStringExtra("url");
        ListIterator<Pokemon> list = Constants.PokeList.listIterator();
        while (list.hasNext()) {
            Pokemon x = list.next();
            String comp = x.getUrl();
            if (comp.equals(url)){
                poke = x;
            }
        }
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        caughtTextView = findViewById(R.id.caught);
        desc = findViewById(R.id.desc);
        catching = findViewById(R.id.button);
        pixelmon = findViewById(R.id.imageView);
        preferences = PreferenceManager.getDefaultSharedPreferences(this);
        editor = preferences.edit();
        load();
    }

    public void load() {
        type1TextView.setText("");
        type2TextView.setText("");
        try {
            if (preferences.contains(poke.getName())) {
                caught = true;
                caughtTextView.setText("[Caught]");
                caughtTextView.setVisibility(View.VISIBLE);
                catching.setText("Release?");
            } else {
                caught = false;
                catching.setText("Catch Me!");
            }
        }
        catch (NullPointerException e){
            caught = false;
            catching.setText("Catch Me!");
        }
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    String name = response.getString("name");
                    int id = response.getInt("id");
                    nameTextView.setText(name.substring(0,1).toUpperCase() + name.substring(1));
                    numberTextView.setText(String.format("#%05d", id));
                    loaddesc(id);
                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");
                        type = type.substring(0,1).toUpperCase() + type.substring(1);
                        if (slot == 1) {
                            type1TextView.setText(type);
                            type1TextView.setVisibility(View.VISIBLE);
                        }
                        else if (slot == 2) {
                            type2TextView.setText(type);
                            type2TextView.setVisibility(View.VISIBLE);
                        }

                    }
                    try {
                        new DownloadSpriteTask().execute(response.getJSONObject("sprites")
                                .getString("front_default"));

                    }
                    catch (JSONException e){
                        Log.e("cs50", "Pokemon Image JSON Error");
                    }
                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon JSON Error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon Details Error", error);
            }
        });
        requestQueue.add(request);
    }
    public void toggleCatch(View view) {
        if (!caught){
            if (Math.random() > 0.5){
                caughtTextView.setText("[Caught]");
                caughtTextView.setVisibility(View.VISIBLE);
                catching.setText("Release?");
                editor.putBoolean(poke.getName(),true);
                caught = true;
            }
            else {
                caughtTextView.setText("Not Caught, Try again.");
                caughtTextView.setVisibility(View.VISIBLE);
            }
        }
        else{
            editor.remove(poke.getName());
            caughtTextView.setVisibility(View.GONE);
            catching.setText("Catch Me!");
            caught = false;
        }
        editor.apply();
    }
    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                return BitmapFactory.decodeStream(url.openStream());
            }
            catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }
        @Override
        protected void onPostExecute(Bitmap bitmap) {
            pixelmon.setImageBitmap(bitmap);
        }
    }
    private void loaddesc(int id) {
        String URL = String.format("https://pokeapi.co/api/v2/pokemon-species/%d", id);
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, URL, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    desc.setText(response.getJSONArray("flavor_text_entries").getJSONObject(0).getString("flavor_text"));
                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon JSON Error [#]", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon Details Error", error);
            }
        });
        requestQueue.add(request);
    }
}

