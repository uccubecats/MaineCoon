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
		
		/* Determine if "--help" was passed into the program as an argument. */
		boolean wasHelpSpecified = false;
		for(int i = 0; i < args.length; i++) {
			if(args[i].compareToIgnoreCase("--help") == 0) {
				wasHelpSpecified = true;
				break;
			}
		}
		
		/* If "--help" was specified as an argument, then print the help text and exit the program. */
		if(wasHelpSpecified) {
			printHelpText();
			return;
		}
		
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
				printConsoleOutput("Copying: " + copyList.get(i).getName());
				copyFile(copyList.get(i), new File(PATH_OUT + File.separator + copyList.get(i).getName()));
				printConsoleOutput("Copied: " + copyList.get(i).getName());
				
				/* If it was a linux/unix executable, "fix it" after copying it. */
				if(!copyList.get(i).getName().contains(".")) {
					Process p;
					try {
						printConsoleOutput("Running 'chmod': " + copyList.get(i).getName());
						p = Runtime.getRuntime().exec("chmod +x " + String.valueOf(PATH_OUT + File.separator + copyList.get(i).getName()));
						p.waitFor();
						printConsoleOutput("Ran 'chmod': " + copyList.get(i).getName());
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			
			/* Catch exceptions and print them. */
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		/* Copy all specified Python scripts to the dist directory. */
		for(int i = 0; i < args.length; i++) {
			
			/* Verify that the specified file is valid. */
			File currPyFile = new File(buildDir.getAbsolutePath() + File.separator + args[i]);
			if(currPyFile.exists()) {
		
				/* Create a list of all Python files specified as command-line arguments. */
				List<File> pythonFilesList = new ArrayList<File>();
				List<String> relativePath = new ArrayList<String>();
				findPyFiles(currPyFile, pythonFilesList, relativePath, "");
				
				/* Try to copy the files to the dist directory. */
				for(int j = 0; j < pythonFilesList.size(); j++) {
					try {
						printConsoleOutput("Copying: " + relativePath.get(j) + File.separator + pythonFilesList.get(j).getName());
						File rootFile = new File(PATH_OUT + File.separator + relativePath.get(j));
						rootFile.mkdirs();
						copyFile(pythonFilesList.get(j), new File(rootFile.getAbsolutePath() + File.separator + pythonFilesList.get(j).getName()));
						printConsoleOutput("Copied: " + relativePath.get(j) + File.separator + pythonFilesList.get(j).getName());
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
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
					printConsoleOutput("Discovered Library: " + subDirs[i].getName());
					copyList.add(subDirs[i]);
				} else if(subDirs[i].getAbsolutePath().toLowerCase().endsWith(".dll")) {
					printConsoleOutput("Discovered Library: " + subDirs[i].getName());
					copyList.add(subDirs[i]);
				
				/* Check to see if the current file is an executable file, if so, add it. */
				} else if(subDirs[i].canExecute()) {
					if(subDirs[i].getAbsolutePath().toLowerCase().endsWith(".exe")) {
						printConsoleOutput("Discovered Executable: " + subDirs[i].getName());
						copyList.add(subDirs[i]);
					} else if(!subDirs[i].getName().toLowerCase().contains(".")) {
						if(subDirs[i].getName().compareToIgnoreCase("Makefile") != 0) {
							printConsoleOutput("Discovered Executable: " + subDirs[i].getName());
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
	
	/**
	 * Function used to create a list of the Python scripts to the dist directory.
	 *
	 * @param currDirFull File used to specify the current directory to be referenced by the function.
	 * @param fileList List of Files used to keep track of the Files (scripts) to copy.
	 * @param relativePath List of Strings used to keep track of a local directory structure for copying.
	 * @param currDir String used to keep track of the local, relative path for building the relativePath list.
	 */
	private static void findPyFiles(File currDirFull, List<File> fileList, List<String> relativePath, String currDir) {
		
		/* Get a list of all files and directories in the current file. */
		File[] subDirs = currDirFull.listFiles();
		
		/* Go through each file in the directory. */
		for(int i = 0; i < subDirs.length; i++) {
			if(subDirs[i].isFile()) {
				
				/* Determine if the current file in the directory is a python script and add it if so. */
				if(subDirs[i].getName().toLowerCase().endsWith(".py")) {
					printConsoleOutput("Discovered Python Script: " + currDir + File.separator + subDirs[i].getName());
					fileList.add(subDirs[i]);
					relativePath.add(currDir);
				}
				
			/* If the file is actually a directory, recursively call the findPyFiles function. */
			} else {
				findPyFiles(subDirs[i], fileList, relativePath, currDir + (currDir.equals("") ? "" : File.separator) + subDirs[i].getName());
			}
		}
	}
	
	/**
	 * Function used to print updates to the console with a tag for the application.
	 */
	private static void printConsoleOutput(String consoleText) {
		System.out.println("    [DistPackage]: " + consoleText);
	}
	
	/**
	 * Function used to print the help text to the terminal or command-prompt.
	 */
	private static void printHelpText() {
		System.out.println("");
		System.out.println("This utility is designed to copy the required files from the '../build' directory to the '../dist' directory.");
		System.out.println("Usage: java -jar DistPackage.jar [ARG 1] [ARG 2]...");
		System.out.println("");
		System.out.println("Each 'ARG' listed in the usage section refers to a sub-directory in the project's src folder.");
		System.out.println("These directories are the search locations for any Python scripts which are required to be copied (recursively).");
		System.out.println("");
	}
}
