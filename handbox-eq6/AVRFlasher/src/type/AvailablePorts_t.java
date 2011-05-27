/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package type;

/**
 *
 * @author Huebener.Se
 */

import gnu.io.*; // RXTX
import java.io.*;
import java.util.Enumeration;
import java.util.ArrayList;
import uart.*;
//import java.util.concurrent.Semaphore;

public class AvailablePorts_t {
	public CommPortIdentifier PortID;
	public String PortName;	
	public int baudrate;
	public int dataBits;
	public int stopBits;
	public int parity;	
	public SerialPort sp;
	public OutputStream os;
	public InputStream is;
	public boolean PortOpen;
	public boolean test;
	public SenderTask SenderTaskThread = null;
	//public final Semaphore data_available = new Semaphore(1, true);
	
	public AvailablePorts_t(CommPortIdentifier spid, String spn) {
		this.PortID = spid;
		this.PortName = spn;
		this.baudrate = 9600;
		this.dataBits = SerialPort.DATABITS_8;
		this.stopBits = SerialPort.STOPBITS_1;
		this.parity = SerialPort.PARITY_NONE;		
		this.sp = null;
		this.os = null;
		this.PortOpen = false;
		this.test = false;
	}

}
