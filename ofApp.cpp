#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	ofIcoSpherePrimitive ico_sphere;
	ico_sphere = ofIcoSpherePrimitive(200, 3);
	this->triangle_list = ico_sphere.getMesh().getUniqueFaces();

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 60 < 45) {

		this->noise_param += ofMap(ofGetFrameNum() % 60, 0, 45, 0.05, 0);
	}

	this->mesh_list.clear();
	for (int i = 0; i < this->triangle_list.size(); i++) {

		auto triangle = this->triangle_list[i];
		auto avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.x * 0.01, avg.y * 0.01, avg.z * 0.01, this->noise_param);

		vector<glm::vec3> vertices;
		vertices.push_back(glm::normalize(glm::vec3(triangle.getVertex(0) - avg) * 0.9 + avg) * ofMap(noise_value, 0, 1, 50, 350));
		vertices.push_back(glm::normalize(glm::vec3(triangle.getVertex(1) - avg) * 0.9 + avg) * ofMap(noise_value, 0, 1, 50, 350));
		vertices.push_back(glm::normalize(glm::vec3(triangle.getVertex(2) - avg) * 0.9 + avg) * ofMap(noise_value, 0, 1, 50, 350));

		ofMesh mesh;

		mesh.addVertex(glm::vec3());
		mesh.addVertices(vertices);

		mesh.addIndex(0);
		mesh.addIndex(1);
		mesh.addIndex(2);

		mesh.addIndex(0);
		mesh.addIndex(2);
		mesh.addIndex(3);

		mesh.addIndex(0);
		mesh.addIndex(1);
		mesh.addIndex(3);

		mesh.addIndex(1);
		mesh.addIndex(2);
		mesh.addIndex(3);

		this->mesh_list.push_back(mesh);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);
	ofRotateX(ofGetFrameNum() * 0.25);

	for (auto& mesh : this->mesh_list) {

		ofSetColor(39);
		mesh.drawFaces();

		ofSetColor(239);
		mesh.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}