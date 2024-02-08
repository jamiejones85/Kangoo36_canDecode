#include "KangooCan.h"

KangooCan::KangooCan() {

};

void KangooCan::handleFrame155(const uint8_t* data) {
    stateOfCharge = (float) ((data[4] << 8) + data[5]) * 0.0025;
    maxCharging = data[0] * 300;
}

void KangooCan::handleFrame424(const uint8_t* data) {
    stateOfHealth = data[5];
    lowestCellTemp = (uint8_t)(data[4]) - 40;
    highestCellTemp = (uint8_t)(data[7]) - 40;
    maxInputPower = data[2] / 2;
    maxOutputPower = data[3] / 2;

}

void KangooCan::handleFrame425(const uint8_t* data) {
    lowestCellVolt = (float)((((data[6] & 0x01) << 8) + data[7]) * 0.01) + 1;
    highestCellVolt = (float)((((data[6] & 0x03) << 8) + ((data[5] & 0xFE) >> 1)) * 0.01) + 1;
    remainingKHW = (float)(data[1] * 0.1);

}

bool KangooCan::ProcessISOTPResponse(const uint8_t* data) {
    uint8_t length = sizeof(data);
    //start of response
    if (data[0] == 0x10 && data[2] == 0x61) {
        remainingByteCount = data[1];
        byteCount = 0;
        currentPID = data[3];
    }
   if (currentPID == 0x01) {
        return handlePID01Frame(data);
    }
    if (currentPID == 0x61) {
        return handlePID61Frame(data);
    }
    if (currentPID == 0x66) {
        return handlePID66Frame(data);
    }
    if (currentPID == 0x03) {
        return handlePID03Frame(data);
    }
    if (currentPID == 0x41) {
        return handlePID41Frame(data);
    }
    if (currentPID == 0x42) {
        return handlePID42Frame(data);
    }
    return false;
}

bool KangooCan::handlePID61Frame(const uint8_t* data) {
    if (data[0] == 0x10) {
        return true; //requst next data
    } else if (data[0] == 0x21) {
        //amphours
        ampHoursRaw = (data[1] << 24) + (data[2] << 16) + (data[3] << 8) + data[4];
        packHealthRaw = data[5];
        totalKilometers = (data[6] << 24) + (data[7] << 16);
        return true; //requst next data
    } else if (data[0] == 0x22) {
        totalKilometers = totalKilometers + data[1];

        return false; //requst next data
    }

    return false;
}

bool KangooCan::handlePID66Frame(const uint8_t* data) {
    if (data[0] == 0x10) {
        quickchargeCount = (data[4] << 8) + data[5];
        normalchargeCount = (data[6] << 8) + data[7];
        return true; //requst next data
    } else if (data[0] == 0x21) {
        fullchargeCount = (data[0] << 8) + data[1];
        partialchargeCount = (data[2] << 8) + data[3];
        return true; //requst next data
    } else if (data[0] == 0x22) {
        return false; //requst next data
    }

    return false;
}

bool KangooCan::handlePID03Frame(const uint8_t* data) {
    if (data[0] == 0x10) {
        return true;
    } else if (data[0] == 0x21) {
        batteryTemperature = (data[1] << 8) + data[2];
        highestMilV = (data[7] << 8);
        return true;
    } else if (data[0] == 0x22) {
        highestMilV = highestMilV + data[1];
        lowestMilV = (data[2] << 8) + data[3];
        return true;
    }  else if (data[0] == 0x23) {
        return true;
    } else if (data[0] == 0x24) {
        //SOC?
        return true;
    } else if (data[0] == 0x25) {
        //internal resistance?]
        //real SOC?
        return true;
    } else if (data[0] == 0x26) {
        //real SOC?
        //ah?
        return true;
    } else if (data[0] == 0x27) {
        //max charge? isolation?
        maxChargingRaw = (data[1] << 8) + data[2];
        return false;
    }

    return false;
}

bool KangooCan::handlePID04Frame(const uint8_t* data) {
    return false;
}

bool KangooCan::handlePID01Frame(const uint8_t* data) {
    if (data[0] == 0x10) {
        return true;
    } else if (data[0] == 0x21) {
        batteryCurrent = (data[3] << 24) + (data[4] << 16) + (data[5] << 8) + (data[6]);
        return true;
    } else if (data[0] == 0x22) {
        return true;
    }  else if (data[0] == 0x23) {
        maxInputPowerRaw = (data[3] << 8) + (data[4]);
        maxOutputPowerRaw = (data[5] << 8) + (data[6]);

        return true;
    } else if (data[0] == 0x24) {
        return true;
    } else if (data[0] == 0x25) {
        return true;
    } else if (data[0] == 0x26) {
        return true;
    } else if (data[0] == 0x27) {
        return false;
    }

    return false;
}

bool KangooCan::handlePID41Frame(const uint8_t* data) {
    if (data[0] == 0x10) {
        looped = false;
        cellVoltages[0] = (data[4] << 8) + data[5];
        cellVoltages[1] = (data[6] << 8) + data[7];
        return true;
    } else if (!looped && data[0] == 0x21) {
        cellVoltages[2] = (data[1] << 8) + data[2];
        cellVoltages[3] = (data[3] << 8) + data[4];
        cellVoltages[4] = (data[5] << 8) + data[6];
        cellVoltages[5] = (data[7] << 8);
        return true;
    } else if (!looped && data[0] == 0x22) {
        cellVoltages[5] = cellVoltages[5] + data[1];
        cellVoltages[6] = (data[2] << 8) + data[3];
        cellVoltages[7] = (data[4] << 8) + data[5];
        cellVoltages[8] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x23) {
        cellVoltages[9] = (data[1] << 8) + data[2];
        cellVoltages[10] = (data[3] << 8) + data[4];
        cellVoltages[11] = (data[5] << 8) + data[6];
        cellVoltages[12] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x24) {
        cellVoltages[12] = cellVoltages[12] + data[1];
        cellVoltages[13] = (data[2] << 8) + data[3];
        cellVoltages[14] = (data[4] << 8) + data[5];
        cellVoltages[15] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x25) {
        cellVoltages[16] = (data[1] << 8) + data[2];
        cellVoltages[17] = (data[3] << 8) + data[4];
        cellVoltages[18] = (data[5] << 8) + data[6];
        cellVoltages[19] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x26) {
        cellVoltages[19] = cellVoltages[19] + data[1];
        cellVoltages[20] = (data[2] << 8) + data[3];
        cellVoltages[21] = (data[4] << 8) + data[5];
        cellVoltages[22] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x27) {
        cellVoltages[23] = (data[1] << 8) + data[2];
        cellVoltages[24] = (data[3] << 8) + data[4];
        cellVoltages[25] = (data[5] << 8) + data[6];
        cellVoltages[26] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x28) {
        cellVoltages[26] = cellVoltages[26] + data[1];
        cellVoltages[27] = (data[2] << 8) + data[3];
        cellVoltages[28] = (data[4] << 8) + data[5];
        cellVoltages[29] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x29) {
        cellVoltages[30] = (data[1] << 8) + data[2];
        cellVoltages[31] = (data[3] << 8) + data[4];
        cellVoltages[32] = (data[5] << 8) + data[6];
        cellVoltages[33] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x2A) {
        cellVoltages[33] = cellVoltages[33] + data[1];
        cellVoltages[34] = (data[2] << 8) + data[3];
        cellVoltages[35] = (data[4] << 8) + data[5];
        cellVoltages[36] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x2B) {
        cellVoltages[37] = (data[1] << 8) + data[2];
        cellVoltages[38] = (data[3] << 8) + data[4];
        cellVoltages[39] = (data[5] << 8) + data[6];
        cellVoltages[40] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x2C) {
        cellVoltages[40] = cellVoltages[40] + data[1];
        cellVoltages[41] = (data[2] << 8) + data[3];
        cellVoltages[42] = (data[4] << 8) + data[5];
        cellVoltages[43] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x2D) {
        cellVoltages[44] = (data[1] << 8) + data[2];
        cellVoltages[45] = (data[3] << 8) + data[4];
        cellVoltages[46] = (data[5] << 8) + data[6];
        cellVoltages[47] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x2E) {
        cellVoltages[47] = cellVoltages[47] + data[1];
        cellVoltages[48] = (data[2] << 8) + data[3];
        cellVoltages[49] = (data[4] << 8) + data[5];
        cellVoltages[50] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x2F) {
        cellVoltages[51] = (data[1] << 8) + data[2];
        cellVoltages[52] = (data[3] << 8) + data[4];
        cellVoltages[53] = (data[5] << 8) + data[6];
        cellVoltages[54] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x20) {
        looped = true;
        cellVoltages[54] = cellVoltages[54] + data[1];
        cellVoltages[55] = (data[2] << 8) + data[3];
        cellVoltages[56] = (data[4] << 8) + data[5];
        cellVoltages[57] = (data[6] << 8) + data[7];
        return true;
        //21 and 22 will come again
    } else if (looped && data[0] == 0x21) {
        //21 and 22 will come again
        cellVoltages[58] = (data[1] << 8) + data[2];
        cellVoltages[59] = (data[3] << 8) + data[4];
        cellVoltages[60] = (data[5] << 8) + data[6];
        cellVoltages[61] = (data[7] << 8);
        return true;
    } else if (looped && data[0] == 0x22) {
        //21 and 22 will come again
        looped = false;
        cellVoltages[61] = cellVoltages[61] + data[1];
        return false;
    }
    return false;
}
bool KangooCan::handlePID42Frame(const uint8_t* data) {
    if (data[0] == 0x10) {
        cellVoltages[62] = (data[4] << 8) + data[5];
        cellVoltages[63] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x21) {
        cellVoltages[64] = (data[1] << 8) + data[2];
        cellVoltages[65] = (data[3] << 8) + data[4];
        cellVoltages[66] = (data[5] << 8) + data[6];
        cellVoltages[67] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x22) {
        cellVoltages[67] = cellVoltages[67] + data[1];
        cellVoltages[68] = (data[2] << 8) + data[3];
        cellVoltages[69] = (data[4] << 8) + data[5];
        cellVoltages[70] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x23) {
        cellVoltages[71] = (data[1] << 8) + data[2];
        cellVoltages[72] = (data[3] << 8) + data[4];
        cellVoltages[73] = (data[5] << 8) + data[6];
        cellVoltages[74] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x24) {
        cellVoltages[74] = cellVoltages[74] + data[1];
        cellVoltages[75] = (data[2] << 8) + data[3];
        cellVoltages[76] = (data[4] << 8) + data[5];
        cellVoltages[77] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x25) {
        cellVoltages[78] = (data[1] << 8) + data[2];
        cellVoltages[79] = (data[3] << 8) + data[4];
        cellVoltages[80] = (data[5] << 8) + data[6];
        cellVoltages[81] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x26) {
        cellVoltages[81] = cellVoltages[81] + data[1];
        cellVoltages[82] = (data[2] << 8) + data[3];
        cellVoltages[83] = (data[4] << 8) + data[5];
        cellVoltages[84] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x27) {
        cellVoltages[85] = (data[1] << 8) + data[2];
        cellVoltages[86] = (data[3] << 8) + data[4];
        cellVoltages[87] = (data[5] << 8) + data[6];
        cellVoltages[88] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x28) {
        cellVoltages[88] = cellVoltages[88] + data[1];
        cellVoltages[89] = (data[2] << 8) + data[3];
        cellVoltages[90] = (data[4] << 8) + data[5];
        cellVoltages[91] = (data[6] << 8) + data[7];
        return true;
    } else if (data[0] == 0x29) {
        cellVoltages[92] = (data[1] << 8) + data[2];
        cellVoltages[93] = (data[3] << 8) + data[4];
        cellVoltages[94] = (data[5] << 8) + data[6];
        cellVoltages[95] = (data[7] << 8);
        return true;
    } else if (data[0] == 0x2A) {
        cellVoltages[95] = cellVoltages[95] + data[1];
        packVoltage = (data[2] << 8) + data[3];
        daigPackVoltage = (data[4] << 8) + data[5]; //? not sure what this is for
        return false;
    }
    return false;
}

void KangooCan::printData() {
    //not sure about comented out values 
    cout << "------ Free Frames Data --------" << endl << endl;
    cout << "SoC: " << stateOfCharge << "%" << endl;
    cout << "SoH: " << stateOfHealth << "%" << endl;
    cout << "Lowest Cell: " << lowestCellVolt << "V" <<endl;
    cout << "Highest Cell: " << highestCellVolt << "V" <<endl;
    cout << "Remaining KWH: " << remainingKHW << "kWh" <<endl;
    cout << "Highest Temp: " << (int)highestCellTemp << "C" << endl;
    cout << "Lowest Temp: " << (int)lowestCellTemp << "C" << endl;
    cout << "Max Charing Rate: " << (int) maxCharging << "W" << endl;
    cout << "Max Input Power: " << (int) maxInputPower << "kW" << endl;
    cout << "Max Output Power: " << (int) maxOutputPower << "kW" << endl;

    cout << endl << endl;
    cout << "------ ISOTP Kangoo Data -------" << endl << endl;

    //cout << "AmpHours: " << (ampHoursRaw / 10000) << "?" << endl;
    cout << "Battery Current: " << batteryCurrent << "mA" << endl;
    cout << "State Of Health: " << (packHealthRaw / 2) << "%" << endl;
    cout << "QuickCharge Count: " << quickchargeCount << endl;
    cout << "NormalCharge Count: " << normalchargeCount << endl;
    //cout << "FullCharge Count: " << fullchargeCount << "?" << endl;
    //cout << "PartialCharge Count: " << partialchargeCount << "?" << endl;
    //cout << "Total Kilometers: " << totalKilometers << endl;
    cout << "Max Input: " << (float)maxInputPowerRaw / 100 << " kW" << endl;
    cout << "Max Output: " << (float)maxOutputPowerRaw / 100 << " kW" << endl;

    //cout << "Battery Temperature: " << (float)batteryTemperature / 1000 << " C" << endl;

    cout << "Lowest Cell: " <<  (float)lowestMilV / 100 << " V" << endl;
    cout << "Highest Cell: " <<  (float)highestMilV / 100 << " V" << endl;

    cout << "Max Charging: " <<  maxChargingRaw / 10 << " kW" << endl;
    cout << "Pack Voltage: " << (float) packVoltage/100 << " V" << endl;
    cout << "Diagnostic Pack Voltage: " << (float) daigPackVoltage/100 << " V" << endl;

    // for (int i = 0; i < 96; i++) {
    //     cout << "Cell " <<  i << ": " << cellVoltages[i] << "mV" << endl;
    // }

}