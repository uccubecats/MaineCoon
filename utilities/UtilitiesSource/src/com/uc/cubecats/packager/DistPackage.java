package com.uc.cubecats.packager;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * This class acts as a simple utility designed to "package" CubeCats
 * formatted projects into its distribution (dist) directory from the
 * build directory.  It essentially copies the first-level executable
 * (the application) and all contained dynamic libraries.
 * 
 * @author Tyler Parcell
 * @version 1.0
 *
 */
public class DistPackage {

	// Constants
	private static String PATH_IN = "../build";		// String used to reference the application's build directory.
	private static String PATH_OUT = "../dist";		// String used to reference the application's dist directory.
	
	/**
	 * This function serves as the entry point into the utility to begin
	 * the file copying process.  Currently, command-line arguments are
	 * not supported.
	 * 
	 * @param args Command-line arguments, which are not supported currently.
	 */
	public static void main(String[] args) {
		
		/* Get a reference to the build path. */
		File buildDir = new File(PATH_IN);
		
		/* Verify that the build path exists before proceeding. */
		if(!(buildDir.exists() && buildDir.isDirectory())) {
			return;
		}
		
		/* If the "dist" path doesn't exist, create it. */
		File distDir = new File(PATH_OUT);
		if(!distDir.exists()) {
			distDir.mkdir();
		}
		
		/* Get a list of executables and libraries to copy. */
		List<File> copyList = new ArrayList<File>();
		evaluateFile(buildDir, copyList);
		
		/* Begin going through each file in the list. */
		int copyListSize = copyList.size();
		for(int i = 0; i < copyListSize; i++) {
			
			/* Attempt to copy the file to the "dist" directory. */
			try {
				copyFile(copyList.get(i), new File(PATH_OUT + File.separator + copyList.get(i).getName()));
				
				/* If it was a linux/unix executable, "fix it" after copying it. */
				if(!copyList.get(i).getName().contains(".")) {
					Process p;
					try {
						p = Runtime.getRuntime().exec("chmod +x " + String.valueOf(PATH_OUT + File.separator + copyList.get(i).getName()));
						p.waitFor();
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			
			/* Catch exceptions and print them. */
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	/**
	 * This function is designed to recursively build a list of libraries and executables
	 * by leveraging the evaluateFileHelper function also located in this class.
	 * Specifically, this function also copies executable files, not just libraries.
	 * 
	 * @param buildDir The directory to get the files from.
	 * @param copyList The list to put the files to copy in.
	 */
	private static void evaluateFile(File buildDir, List<File> copyList) {
		
		/* Get a list of all files and directories in the current file. */
		File[] subDirs = buildDir.listFiles();
		
		/* Go through each file in the directory. */
		for(int i = 0; i < subDirs.length; i++) {
			
			/* If the file is a file, check to see if it's one we want to copy. */
			if(subDirs[i].isFile()) {
				
				/* Check to see if the current file is a library, if so, add it. */
				if(subDirs[i].getAbsolutePath().toLowerCase().endsWith(".so")) {
					copyList.add(subDirs[i]);
				} else if(subDirs[i].getAbsolutePath().toLowerCase().endsWith(".dll")) {
					copyList.add(subDirs[i]);
				
				/* Check to see if the current file is an executable file, if so, add it. */
				} else if(subDirs[i].canExecute()) {
					if(subDirs[i].getAbsolutePath().toLowerCase().endsWith(".exe")) {
						copyList.add(subDirs[i]);
					} else if(!subDirs[i].getName().toLowerCase().contains(".")) {
						if(subDirs[i].getName().compareToIgnoreCase("Makefile") != 0) {
							copyList.add(subDirs[i]);
						}
					}
				}
			
			/* If the file is actually a directory, recursively call the helper copy function. */
			} else {
				evaluateFileHelper(subDirs[i], copyList);
			}
		}
	}

	/**
	 * Function used to recursively create a list of libraries starting at the given directory.
	 * 
	 * @param buildDir The directory to get the files from.
	 * @param copyList The list to put the files to copy in.
	 */
	private static void evaluateFileHelper(File buildDir, List<File> copyList) {
		
		/* Get a list of all files and directories in the current file. */
		File[] subDirs = buildDir.listFiles();
		
		/* Go through each file in the directory. */
		for(int i = 0; i < subDirs.length; i++) {
			if(subDirs[i].isFile()) {
				
				/* Check to see if the current file is a library, if so, add it. */
				if(subDirs[i].getAbsolutePath().toLowerCase().endsWith(".so")) {
					copyList.add(subDirs[i]);
				} else if(subDirs[i].getAbsolutePath().toLowerCase().endsWith(".dll")) {
					copyList.add(subDirs[i]);
				}
				
			/* If the file is actually a directory, recursively call the helper copy function. */
			} else {
				evaluateFileHelper(subDirs[i], copyList);
			}
		}
	}
	
	/**
	 * Function used to copy a given file to the destination file.
	 * 
	 * @param src The file to copy from.
	 * @param dst The file to copy to.
	 * @throws IOException
	 */
	private static void copyFile(File src, File dst) throws IOException {
		
		/* Open up both the source and destination locations. */
		FileInputStream inStream = new FileInputStream(src);
		FileOutputStream outStream = new FileOutputStream(dst);
		
		/* Create a buffer to store the data in while copying. */
		byte[] buffer = new byte[1024];

		/* Attempt to copy the file. */
		try {
			int length;
			while((length = inStream.read(buffer)) > 0) {
					outStream.write(buffer, 0, length);
			}
		
		/* If the operation fails, output the error. */
		} catch (IOException e) {
			e.printStackTrace();
		
		/* Close all file references. */
		} finally {
			inStream.close();
			outStream.flush();
			outStream.close();
		}
		
	}
	
}
