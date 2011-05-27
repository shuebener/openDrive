/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gui;

import java.io.*;
import java.util.Properties;

public class Settings extends Properties {

	protected String SettingsFile = System.getProperty("user.dir") +"/avrf_settings.xml";

	public void SetFileName(String File) {
		this.SettingsFile = File;	
	}	
	
	public void LoadXML() {
		try {
			this.loadFromXML(new FileInputStream(this.SettingsFile));
		} catch (Exception e) {
			System.out.println("Warning: "+ e.getMessage());
		}
	}
	
	public void SaveXML() {
		try {
			this.storeToXML(new FileOutputStream(this.SettingsFile), null, "UTF-8");
		} catch (Exception e) {
			System.out.println("Warning: "+ e.getMessage());
		}		
	}
	
/*	
	@Override public synchronized Object setProperty(String key, String value) {
		Object rtn = super.setProperty(key, value);
		this.SaveXML();
		
		return(rtn);
	}
*/
	
}
