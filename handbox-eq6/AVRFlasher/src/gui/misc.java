
package gui;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.Toolkit;


public class misc {

	public static String Int2HexString(int Hex) {
		String HexStr = Integer.toHexString(Hex).toUpperCase();
		switch(HexStr.length()) {
			case 0:		HexStr = "0000"; break;
			case 1:		HexStr = "000"+ HexStr; break;
			case 2:		HexStr = "00"+ HexStr; break;
			case 3:		HexStr = "0"+ HexStr; break;
		}
		
		return(HexStr);
	}
}
