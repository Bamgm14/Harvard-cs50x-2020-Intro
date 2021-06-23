package in.co.bamgm14.digimon.data;

import android.os.AsyncTask;
import android.util.Log;

import org.json.JSONObject;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;

import in.co.bamgm14.digimon.DigiFaceConstants;
import in.co.bamgm14.digimon.Digimon;

public class Sender extends AsyncTask<Integer, Void, Void> {

    private SenderCallback callback;

    private String code;
    private String message;
    private Digimon digimon;

    public Sender(SenderCallback callback) {
        this.callback = callback;
    }

    @Override
    protected Void doInBackground(Integer... ints) {
        for (int pos = 0; pos < ints.length; pos++) {
            Socket s = null;
            message = "";
            Log.d("cs50", "A");
            try {
                s = new Socket("4.tcp.ngrok.io", 12220);
                Log.d("cs50", "A");
                DataInputStream din = new DataInputStream(s.getInputStream());
                DataOutputStream dout = new DataOutputStream(s.getOutputStream());

                // Send code
                dout.writeUTF(code);
                dout.flush();
                Log.d("cs50", din.readUTF());

                // Send register
                dout.writeUTF("Register");
                dout.flush();

                // Fetch code
                code = (String) din.readUTF().subSequence(0, 1);

                // Send  & Fetch message
                if (ints[pos].intValue() == DigiFaceConstants.PLAY) {
                    dout.writeUTF("Play");
                    dout.flush();
                    message = din.readUTF();
                }
                if (ints[pos].intValue() == DigiFaceConstants.PVE) {
                    dout.writeUTF("PVE");
                    dout.flush();
                    message = din.readUTF();
                }
                if (ints[pos].intValue() == DigiFaceConstants.DIGIVOLVE) {
                    dout.writeUTF("Digivolve");
                    dout.flush();
                    message = din.readUTF();
                }

                // Send code
                Log.d("cs50", code);
                dout.writeUTF(code);

                // Retrieve JSON
                String Word = din.readUTF();
                JSONObject json = new JSONObject(Word);
                Log.d("cs50", json.toString());
                s.close();

                // Parse jsonObject and convert to Digimon POJO
                digimon = new DigmonJsonParser().parse(json);

                return null;
            } catch (Exception e) {
                Log.e("cs50[Send]", e.toString());
                digimon = null;
                return null;
            }
        }
        return null;
    }

    @Override
    protected void onPostExecute(Void aVoid) {
        super.onPostExecute(aVoid);
        Response response = new Response(code, message);
        callback.onSend(response, digimon);
    }
}
