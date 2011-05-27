
package gui;

import java.io.*;
import javax.swing.*;

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
	
	public static int getLineCnt(String File) {
		FileReader fr;
		BufferedReader br;
		int rows = 0;
	
		try {
			fr = new FileReader(File);			
			br = new BufferedReader(fr);			
			while(br.readLine() != null) {
				rows++;
			}
			br.close();
			fr.close();
		} catch(Exception e) {
			
		}
		
		return(rows);
	}
	
	public static int getCBIndexByName(JComboBox CB, String Name) {		
		for(int i=0; i < CB.getItemCount(); i++) {
			if(CB.getItemAt(i).equals(Name)) {
				return(i);
			}
		}
		return(-1);
	}
}
