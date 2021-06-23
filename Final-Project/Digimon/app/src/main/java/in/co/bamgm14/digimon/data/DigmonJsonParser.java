package in.co.bamgm14.digimon.data;

import org.json.JSONException;
import org.json.JSONObject;

import in.co.bamgm14.digimon.Digimon;
import in.co.bamgm14.digimon.MainActivity;

public class DigmonJsonParser {

    /*
     * NOTE: Use constants to define keys
     */
    private static final String KEY_NAME = "name";
    private static final String KEY_TYPE = "type";
    private static final String KEY_STAGE = "stage";
    private static final String KEY_EXPERIENCE = "experience";
    private static final String KEY_BOND = "bond";
    private static final String KEY_IMAGE_URL = "url";

    /*
     * NOTE:
     * - Separate parsing logic from downloading and view rendering logic.
     * - Single Responsibility - Parse JSONObject and convert to Digimon data class.
     */
    public Digimon parse(JSONObject jsonDigimon) throws JSONException {
        String name = jsonDigimon.getString(KEY_NAME);
        String type = jsonDigimon.getString(KEY_TYPE);
        String stage = jsonDigimon.getString(KEY_STAGE);
        Double experience = jsonDigimon.getDouble(KEY_EXPERIENCE);
        Double bond = jsonDigimon.getDouble(KEY_BOND);
        String imageUrl = jsonDigimon.getString(KEY_IMAGE_URL);
        return new Digimon(
                name,
                type,
                stage,
                experience,
                bond,
                imageUrl
        );
    }
}
