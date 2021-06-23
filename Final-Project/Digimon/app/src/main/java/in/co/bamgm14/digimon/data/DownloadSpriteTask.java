package in.co.bamgm14.digimon.data;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.util.Log;

import java.io.IOException;
import java.net.URL;

public class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {

    private DownloadSpriteCallback callback;

    public DownloadSpriteTask(DownloadSpriteCallback callback) {
        this.callback = callback;
    }

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
       callback.onDownloadImage(bitmap);
    }
}

