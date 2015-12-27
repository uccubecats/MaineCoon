package com.uc.cubecats.archiver;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;

public class ArchiveManager {
	
	// Variables
	private FileOutputStream archiveOutputStream;
	private FileInputStream archiveInputStream;
	private ZipOutputStream archiveZipOutputStream;
	private ZipInputStream archiveZipInputStream;
	private List<Pattern> excludePatterns;

	public ArchiveManager() {
		excludePatterns = new ArrayList<Pattern>();
	}
	
	public void extractArchive(File archiveToExtract, File locationToExtractTo, boolean shouldDeleteExistingLocation, boolean shouldMerge) throws IOException {
		
		/* Open the archive. */
		openArchive(archiveToExtract);
		
		/* Attempt to remove the entire output directory if it is desired. */
		if(shouldDeleteExistingLocation && locationToExtractTo.exists()) {
			deleteSubDirsAndFiles(locationToExtractTo);
		
		/* Attempt to create the directories if they don't exist. */
		} else {
			locationToExtractTo.mkdirs();
		}
		
		/* Begin reading in the individual entries from the archive. */
		ZipEntry zipEntry = archiveZipInputStream.getNextEntry();
		while(zipEntry != null) {
			
			/* Get the Zip entry information and prepare to extract the content. */
			String filename = zipEntry.getName();
			File fileToExtract = new File(locationToExtractTo.getAbsolutePath() + File.separator + filename);
			
			/* Create any and all parent directories for the current Zip Entry. */
			new File(fileToExtract.getParent()).mkdirs();
			
			/* Verify that if the file exists, we are allowed to replace it. */
			if(!fileToExtract.exists() || shouldMerge) {
				
				/* Extract archive entry. */
				extractArchiveEntry(zipEntry, fileToExtract);
			
			/* Raise an exception regarding the overwriting of a file without merge permissions. */
			} else {
				// TODO - Raise exception...
			}
			
			/* Get the next Zip Entry. */
			zipEntry = archiveZipInputStream.getNextEntry();
		}
		
		/* Close the archive we extracted from. */
		closeInputArchive();
	}
	
	private void extractArchiveEntry(ZipEntry zipEntry, File fileToExtract) throws IOException {
		System.out.println("Extracting: " + fileToExtract.getName() + "...");
		
		/* Create and open the output file for the current Zip Entry. */
		FileOutputStream fos = new FileOutputStream(fileToExtract);

		/* Create a byte buffer for writing the content to the archive. */
		byte[] byteBuffer = new byte[1024];

		/* Extract the current file to the specified location. */
		int len;
		while((len = archiveZipInputStream.read(byteBuffer)) > 0) {
			fos.write(byteBuffer, 0, len);
		}
		
		/* Close the file. */
		fos.close();
		System.out.println("Extracted: " + fileToExtract.getName());
	}

	private void deleteSubDirsAndFiles(File locationToExtractTo) {
		File[] subDirs = locationToExtractTo.listFiles();
		for(int i = 0; i < subDirs.length; i++) {
			if(subDirs[i].isDirectory()) {
				deleteSubDirsAndFiles(subDirs[i]); 
			}
			subDirs[i].delete();
		}
	}

	public void addExclude(String excludePattern) {
		
		/* Convert the wild-card to the RegEx format. */
		Pattern regex = Pattern.compile("[^*]+|(\\*)");
		Matcher m = regex.matcher(excludePattern);
		StringBuffer b= new StringBuffer();
		while (m.find()) {
		    if(m.group(1) != null) m.appendReplacement(b, ".*");
		    else m.appendReplacement(b, "\\\\Q" + m.group(0) + "\\\\E");
		}
		m.appendTail(b);
		String regExString = b.toString();
		
		/* Add the new exclusion string to the list of excludes. */
		if(File.separatorChar == '/') {
			excludePatterns.add(Pattern.compile(regExString.replace('\\', '/')));
		} else {
			excludePatterns.add(Pattern.compile(regExString.replace('/', '\\')));
		}
	}
	
	public void addExcludes(String[] excludePatterns) {
		for(int i = 0; i < excludePatterns.length; i++) {
			addExclude(excludePatterns[i]);
		}
	}
	
	public void archiveFile(File fileToArchive, File archiveToCreate, boolean shouldDeleteExistingArchive) throws IOException {
		
		/* Create the new archive file, deleting it if it doesn't exist, and we have permission. */
		if(archiveToCreate.exists()) {
			if(shouldDeleteExistingArchive) {
				archiveToCreate.delete();
			} else {
				// TODO - throw exception...
			}
		}
		
		/* Verify that the archive was deleted. */
		if(archiveToCreate.exists()) {
			// TODO - throw exception...
		}
		
		/* Actually create the new archive. */
		setupArchive(archiveToCreate);
		
		/* Archive the file.directory recursively. */
		if(fileToArchive.isDirectory()) {
			archiveFile(fileToArchive, (fileToArchive.getName().equals("..") ? "" : fileToArchive.getName()));
		} else {
			archiveFile(fileToArchive, "");
		}
		
		/* Close the newly created archive. */
		closeOutputArchive();
	}
	
	private void openArchive(File archiveFile) throws FileNotFoundException {
		archiveInputStream = new FileInputStream(archiveFile);
		archiveZipInputStream = new ZipInputStream(archiveInputStream);
		System.out.println("Opened Archive");
	}
	
	private void setupArchive(File archiveFile) throws FileNotFoundException {
		archiveOutputStream = new FileOutputStream(archiveFile);
		archiveZipOutputStream = new ZipOutputStream(archiveOutputStream);
		System.out.println("Setup Archive");
	}
	
	private void addToArchive(File file, String dir) throws IOException {
		
		/* Create a new entry within the archive to place the specified file. */
		String zipString = dir + File.separator + file.getName();
		ZipEntry zipEntry = new ZipEntry(zipString);
		archiveZipOutputStream.putNextEntry(zipEntry);
		System.out.println("Archiving: " + zipString + "...");
		
		/* Create a byte buffer for writing the content to the archive. */
		byte[] byteBuffer = new byte[1024];
		
		/* Write the data to the newly created zip entry. */
		FileInputStream zipFis = new FileInputStream(file);
		int len;
		while((len = zipFis.read(byteBuffer)) > 0) {
			archiveZipOutputStream.write(byteBuffer, 0, len);
		}
		
		/* Close the files/entry. */
		zipFis.close();
		archiveZipOutputStream.closeEntry();
		System.out.println("Archived: " + zipString);
	}
	
	private void closeOutputArchive() throws IOException {
		archiveZipOutputStream.close();
		archiveOutputStream.close();
		System.out.println("Closed Archive");
	}
	
	private void closeInputArchive() throws IOException {
		archiveZipInputStream.close();
		archiveInputStream.close();
		System.out.println("Closed Archive");
	}

	private boolean matchesExcludes(File subDir) {
		
		/* Create a flag to return the status of the search. */
		boolean foundExclude = false;
		
		/* Check the specified file against all the excludes. */
		int excludesLength = excludePatterns.size();
		for(int i = 0; i < excludesLength; i++) {
			if(excludePatterns.get(i).matcher(subDir.getAbsolutePath()).matches()) {
				foundExclude = true;
				break;
			}
		}
		
		/* Return the result.*/
		return foundExclude;
	}

	/**
	 * This function is designed to recursively build a list of libraries and executables
	 * by leveraging the evaluateFileHelper function also located in this class.
	 * Specifically, this function also copies executable files, not just libraries.
	 * 
	 * @param fileToCompress The directory to get the files from.
	 * @param currDir 
	 * @throws IOException
	 */
	private void archiveFile(File fileToCompress, String currDir) throws IOException {
		
		/* Get a list of all files and directories in the current file. */
		File[] subDirs = fileToCompress.listFiles();
		
		/* Go through each file in the directory. */
		for(int i = 0; i < subDirs.length; i++) {
			
			/* Verify that the file doesn't exist in the excludes list. */
			if(!matchesExcludes(subDirs[i])) {
			
				/* If the file is a file, check to see if it's one we want to copy. */
				if(subDirs[i].isFile()) {
					
					/* Add it to the list of files to copy/obtain meta-data from. */
					addToArchive(subDirs[i], currDir);
				
				/* If the file is actually a directory, recursively call the helper copy function. */
				} else {
					archiveFile(subDirs[i], currDir + (currDir.equals("") ? "" : File.separator) + subDirs[i].getName());
				}
			}
		}
	}
	
}
