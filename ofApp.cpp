#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39, 39, 139);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int deg_span = 12;
	int loc_span = 135;

	for (int x = -loc_span * 2; x <= loc_span * 2; x += loc_span) {

		for (int y = -loc_span * 2; y <= loc_span * 2; y += loc_span) {

			auto noise_seed = ofRandom(1000);

			for (int deg = 0; deg < 360; deg += deg_span * 2) {

				for (int radius = 25; radius <= 50; radius += 25) {

					if (radius == 25) {

						auto noise_deg = ofMap(ofNoise(noise_seed, ofGetFrameNum() * 0.035), 0, 1, deg - 125, deg + 125);

						this->mesh.addVertex(glm::vec3(x + radius * cos((noise_deg + deg_span * 0.5) * DEG_TO_RAD), y + radius * sin((noise_deg + deg_span * 0.5) * DEG_TO_RAD), 0));
						this->mesh.addVertex(glm::vec3(x + radius * cos((noise_deg - deg_span * 0.5) * DEG_TO_RAD), y + radius * sin((noise_deg - deg_span * 0.5) * DEG_TO_RAD), 0));

					}
					else {

						this->mesh.addVertex(glm::vec3(x + radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), y + radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), 0));
						this->mesh.addVertex(glm::vec3(x + radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), y + radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), 0));

						this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
						this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->mesh.draw();

	int start = 75;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}