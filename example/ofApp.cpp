#include "ofApp.h"


void ofApp::setup(){

	ofBackground(22);
	ffmpeg.setup("/usr/local/bin/ffmpeg", "/usr/local/bin/ffprobe");
	ffmpeg.setMaxThreadsPerJob(1);
	ffmpeg.setMaxSimulatneousJobs(10);
	
	ofAddListener(ffmpeg.eventJobCompleted, this, &ofApp::onFFmpegJobCompleted);
}

void ofApp::onFFmpegJobCompleted(ofxFFmpegUtils::JobResult & j){

	ofLogNotice() << "FFmpeg Job " << j.jobID << " Complete: " << j.ok;
	ofLogNotice() << "exec time: " << j.results.runTime << " sec";
	ofLogNotice() << "output: " << j.results.combinedOutput;

}

void ofApp::update(){

	float dt = 1./60.;
	ffmpeg.update(dt);
}


void ofApp::draw(){

	ofDrawBitmapString("drag movie files into this window to create image sequences ", 20, 20);

	ffmpeg.drawDebug(20, 40);
}


void ofApp::keyPressed(int key){

}


void ofApp::keyReleased(int key){

}


void ofApp::mouseMoved(int x, int y ){

}


void ofApp::mouseDragged(int x, int y, int button){

}


void ofApp::mousePressed(int x, int y, int button){

}


void ofApp::mouseReleased(int x, int y, int button){

}


void ofApp::windowResized(int w, int h){

}


void ofApp::gotMessage(ofMessage msg){

}


void ofApp::dragEvent(ofDragInfo dragInfo){

	for (auto f : dragInfo.files){

		string movie = f;
		string targetDir = ofFilePath::getEnclosingDirectory(movie);
		string movieFileName = ofFilePath::getBaseName(movie);

		ffmpeg.convertToImageSequence(movie, //file
									  "jpg", //img format
									  1.0, //img compression [0..1]
									  targetDir + "/" + movieFileName, //folder to output to
									  6, //num digits in img sequence file naming
									  ofVec2f(300,300), //resize to fit this box
									  ofVec2f(-1,-1), //crop to match this aspect ratio
									  0 //if cropping, crop balance factor: where to we crop?
									  );
	}
}


