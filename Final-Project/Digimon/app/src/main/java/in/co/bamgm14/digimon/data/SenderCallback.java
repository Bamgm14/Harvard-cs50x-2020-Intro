package in.co.bamgm14.digimon.data;

import in.co.bamgm14.digimon.Digimon;

public interface SenderCallback {
    void onSend(Response response, Digimon digimon);
}
