#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(40);
    ofSetFrameRate(30);
    ofSetEscapeQuitsApp(false);
    
    bIsMouseDown = false;
    
    guiToolbar = new uiToolbar();
    guiToolbar->setup();
    ofAddListener(guiToolbar->newGUIEvent, this, &testApp::guiEvent);
    
    guiInputs = new uiInputs(10, 40, 300, 100);
    guiInputs->setup();
    ofAddListener(guiInputs->newGUIEvent, this, &testApp::guiEvent);

    checkerboard.setSize(10);
    syphon.setup();
    syphonServers.setup();
    ofAddListener(syphonServers.events.serverAnnounced, this, &testApp::syphonServerAnnounced);
    
    elements["Checker"] = new inputElement(&checkerboard, 640, 480);
    elements["Movie"] = new inputElement(&player);
    elements["Webcam"] = new inputElement(&grabber);
    elements["Syphon"] = new inputElement(&syphon);

    guiOutputs = new ofxUISuperCanvas("OUTPUTS", 200, 40, 400, 200);
    guiOutputs->setColorBack(ofxUIColor::darkGray);
    guiOutputs->setVisible(false);
    guiOutputs->addSpacer();
    vector<string> i;
    i.push_back("Wifi");
    i.push_back("Ethernet");
    guiOutputs->addDropDownList("Interfaces", i);
    vector<string> n;
    n.push_back("Node 1");
    n.push_back("Node 2");
    guiOutputs->addSortableList("Nodes", n);
    guiOutputs->addLabelButton("Poll", false);
    //guiOutputs->autoSizeToFitWidgets();
    
    guiSettings = new ofxUISuperCanvas("SETTINGS", 500, 40, 100, 100);
    guiSettings->setColorBack(ofxUIColor::darkGray);
    guiSettings->setVisible(false);
    guiSettings->setGlobalButtonDimension(24);
    guiSettings->addSpacer();
    guiSettings->addImage("Width", new ofImage("Direction Horz.png"), 24, 24);
    guiSettings->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    ofxUINumberDialer* width = guiSettings->addNumberDialer("Width", 1, 1920, 640, 0);
    width->setPadding(8);
    width->getRect()->height = 24;
    guiSettings->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    guiSettings->addImage("Height", new ofImage("Direction Vert.png"), 24, 24);
    guiSettings->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    ofxUINumberDialer* height = guiSettings->addNumberDialer("Height", 1, 1080, 480, 0);
    height->setPadding(8);
    height->getRect()->height = 24;
    guiSettings->autoSizeToFitWidgets();
    ofAddListener(guiSettings->newGUIEvent, this, &testApp::guiEvent);
    
    guiInfo = new ofxUISuperCanvas("INFO", ofGetWindowWidth() - 120, 40, 100, 100);
    guiInfo->setColorBack(ofxUIColor::darkGray);
    guiInfo->setVisible(false);
    guiInfo->addSpacer();
    guiInfo->addLabel("FPS", "30fps", OFX_UI_FONT_MEDIUM);
    guiInfo->addLabel("Mouse", "x:0 y:0", OFX_UI_FONT_MEDIUM);
    //guiInfo->addLabel("Zoom", "Zoom: 100%", OFX_UI_FONT_MEDIUM);
    guiInfo->addSlider("Zoom", 10, 1000, 100);
    guiInfo->autoSizeToFitWidgets();
    ofAddListener(guiInfo->newGUIEvent, this, &testApp::guiEvent);
    
    guiStatus = new ofxUICanvas(0, ofGetWindowHeight()-20, ofGetWindowWidth(), 20);
    guiStatus->setColorBack(ofxUIColor::darkGray);
    guiStatus->setColorFill(ofxUIColor::black);
    guiStatus->addWidgetDown(labelStatus = new ofxUILabel("Status", OFX_UI_FONT_SMALL));


    /*ofxXmlSettings xml;
	xml.loadFile("carlsberg.xml");
	
	//this->width = xml.getAttribute("map", "width", 640, 0);
	//this->height = xml.getAttribute("map", "height", 480, 0);
	
	xml.pushTag("map");
	
	int universes = 1;
	int numAreas = xml.getNumTags("area");
	for (int i=0; i<numAreas; i++) {
		int u = xml.getAttribute("area", "universe", 0, i);
		if (u > universes - 1)
			universes = u + 1;
	}
	mapper.setup(universes);
	
	for (int i=0; i<numAreas; i++) {
		xml.pushTag("area", i);
        mapArea area;
        mapPoint *p = area.points;
		for (int j=0; j<4; j++) {
			p->x = xml.getAttribute("point", "x", 0., j);
			p->y = xml.getAttribute("point", "y", 0., j);
			p ++;
		}
        mapper.addArea(area);
		xml.popTag();
	}
    
	for (int i=0; i<numAreas; i++) {
		int u = xml.getAttribute("area", "universe", 0, i);
		int d = xml.getAttribute("area", "dmx", 0, i) / 3;
        mapper.setAreaUniverse(i, u);
        mapper.setAreaChannel(i, d);
	}
	
	xml.popTag();*/
}

//--------------------------------------------------------------
void testApp::update(){
    
    for (map<string,baseElement*>::iterator it = elements.begin(); it != elements.end(); ++it) {
        if (it->second->type == TYPE_INPUT && it->second->visible) {
            ((inputElement*)it->second)->input->update();
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    canvas.begin();
    
    ofFill();
    ofSetColor(60);
    ofRect(0, 0, canvas.getWidth(), canvas.getHeight());
    ofSetColor(127);
    ofLine(-10, 0, 10, 0);
    ofLine(0, -10, 0, 10);
    ofSetColor(255);
    
    for (map<string,baseElement*>::iterator it = elements.begin(); it != elements.end(); ++it) {
        if (it->second->type == TYPE_INPUT && it->second->visible) {
            inputElement* ie = (inputElement*)it->second;
            
            if (it->first == "Syphon")
                ((ofxSyphonClient*)ie)->bind();
            
            ofTexture & tex = ie->input->getTextureReference();
            //tex.bind();
            glColor3b(255, 255, 255);
            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex2f(ie->corner[0].x, ie->corner[0].y);
            glTexCoord2f(ie->width, 0);
            glVertex2f(ie->corner[1].x, ie->corner[1].y);
            glTexCoord2f(ie->width, ie->height);
            glVertex2f(ie->corner[2].x, ie->corner[2].y);
            glTexCoord2f(0, ie->height);
            glVertex2f(ie->corner[3].x, ie->corner[3].y);
            glEnd();
            //tex.unbind();

            if (it->first == "Syphon")
                ((ofxSyphonClient*)ie)->unbind();
        }
    }
    
    ofTexture &tex = ((inputElement*)elements["Webcam"])->input->getTextureReference();
    //mapper.updatePixels(tex);
    //mapper.drawAreas();
    //mapper.drawPixels(0, 400, 170 * 4, 10);
    
    ofSetColor(255, 244, 0);
    for (vector<baseElement*>::iterator it = selected.begin(); it != selected.end(); ++it) {
        baseElement* be = *it;
        ofNoFill();
        ofRect(be->x+0.5, be->y+0.5, be->width, be->height);
        ofCircle(be->x, be->y, 10);
        ofCircle(be->x+be->width, be->y, 10);
        ofCircle(be->x, be->y+be->height, 10);
        ofCircle(be->x+be->width, be->y+be->height, 10);
        //ofFill();
        //ofRect(be->x+be->width-3.5, be->y+be->height-3.5, 7, 7);
    }
            
    canvas.end();

    if (bIsMouseDown && ((ofxUIImageToggle*)guiToolbar->getWidget("Pointer"))->getValue()) {
        ofEnableAlphaBlending();
        ofNoFill();
        ofSetColor(255, 255, 255, 128);
        ofRect(mouseDown.x, mouseDown.y, ofGetMouseX()-mouseDown.x, ofGetMouseY()-mouseDown.y);
        ofFill();
        ofSetColor(255, 255, 255, 128);
        ofRect(mouseDown.x, mouseDown.y, ofGetMouseX()-mouseDown.x, ofGetMouseY()-mouseDown.y);
    }
}

//--------------------------------------------------------------
void testApp::exit(){
    delete guiToolbar;
    delete guiInputs;
    delete guiOutputs;
    delete guiInfo;
    delete guiStatus;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch(key) {
        case '\t':
            guiToolbar->toggleVisible();
            guiStatus->toggleVisible();
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

    ofxUIWidget* widget = guiToolbar->getWidgetHit(x, y);
    if (widget != NULL) {
        string name = widget->getName();
        string desc = guiToolbar->getWidgetDescription(name);
        labelStatus->setLabel(desc);
    }
    else
        labelStatus->setLabel("");
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    if (((ofxUIImageToggle*)guiToolbar->getWidget("Pointer"))->getValue()) {
        
    }
    if (((ofxUIImageToggle*)guiToolbar->getWidget("Move"))->getValue()) {
        ofPoint p = canvas.pointToCanvas(x, y);
        float xd = (x - ofGetPreviousMouseX()) / canvas.getScale();
        float yd = (y - ofGetPreviousMouseY()) / canvas.getScale();

        for (vector<baseElement*>::iterator it = selected.begin(); it != selected.end(); ++it) {
            it[0]->x += xd;
            it[0]->y += yd;
        }
    }
    if (((ofxUIImageToggle*)guiToolbar->getWidget("Hand"))->getValue()) {
        
        canvas.move(x - mouseDown.x, y - mouseDown.y);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    ofxUIWidget* widget = guiToolbar->getWidgetHit(x, y);
    if (widget != NULL)
        return;
    
    if (((ofxUIImageToggle*)guiToolbar->getWidget("Pointer"))->getValue()) {
        mouseDown.x = x;
        mouseDown.y = y;
        
        ofPoint p = canvas.pointToCanvas(x, y);
        selected.clear();
        for (map<string,baseElement*>::reverse_iterator it = elements.rbegin(); it != elements.rend(); ++it) {
            baseElement* e = it->second;
            if (e->visible && p.x > e->x && p.x < e->x+e->width && p.y > e->y && p.y < e->y+e->height) {
                selected.push_back(e);
                break;
            }
        }
        
        cout << p.x << ", " << p.y << endl;
        
        int index = mapper.findArea(p.x, p.y);
        if (index != -1) {
            mapper.setAreaColor(index, 255, 255, 0);
        }
    }
    if (((ofxUIImageToggle*)guiToolbar->getWidget("Move"))->getValue()) {
        mouseDown = canvas.pointToCanvas(x, y);

        ofPoint p = canvas.pointToCanvas(x, y);
        selected.clear();
        for (map<string,baseElement*>::reverse_iterator it = elements.rbegin(); it != elements.rend(); ++it) {
            baseElement* e = it->second;
            if (e->visible && p.x > e->x && p.x < e->x+e->width && p.y > e->y && p.y < e->y+e->height) {
                selected.push_back(e);
                break;
            }
        }
    }
    if (((ofxUIImageToggle*)guiToolbar->getWidget("Hand"))->getValue()) {
        //mouseDown = canvas.pointToCanvas(x, y);
        mouseDown.x = x - canvas.getX() * canvas.getScale();
        mouseDown.y = y - canvas.getY() * canvas.getScale();
    }
    bIsMouseDown = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    bIsMouseDown = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

    guiStatus->setPosition(0, h - 20);
    guiStatus->setWidth(w);
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e) {
    
    string name = e.getName();
    
    if (name == "Zoom") {
        canvas.zoom(e.getSlider()->getValue());
    }
    if (name == "ZoomIn" && e.getButton()->getValue()) {
        canvas.zoomIn();
    }
    if (name == "ZoomOut" && e.getButton()->getValue()) {
        canvas.zoomOut();
    }
    if (name == "Reset") {
        canvas.move(0, 0);
        canvas.zoom(100);
    }
    if (name == "Inputs") {
        guiInputs->setVisible(e.getToggle()->getValue());
    }
    if (name == "Checkerboard") {
        elements["Checker"]->visible = e.getToggle()->getValue();
    }
    if (name == "CheckerSize") {
        int s = e.getSlider()->getValue() * 2;
        checkerboard.setSize(s);
    }
    if (name == "Movie") {
        if (e.getToggle()->getValue())
            player.play();
        else
            player.stop();
        elements["Movie"]->visible = e.getToggle()->getValue();
    }
    if (name == "BrowseMovie" && e.getButton()->getValue()) {
        ofFileDialogResult result = ofSystemLoadDialog("Select movie file");
        if (result.bSuccess) {
            player.loadMovie(result.filePath);
            elements["Movie"]->width = player.getWidth();
            elements["Movie"]->height = player.getHeight();
        }
    }
    if (name == "WebCam") {
        elements["Webcam"]->visible = e.getToggle()->getValue();
    }
    if (name == "Grabber") {
        if (e.getToggle()->getValue() && !grabber.isInitialized()) {
            grabber.initGrabber(640, 480);
            elements["Webcam"]->width = grabber.getWidth();
            elements["Webcam"]->height = grabber.getHeight();
        }
        if (!e.getToggle()->getValue() && grabber.isInitialized()) {
            grabber.close();
        }
    }
    if (name == "Syphon") {
        elements["Syphon"]->visible = e.getToggle()->getValue();
    }
    if (name == "Servers") {
        ofxUIDropDownList *list = (ofxUIDropDownList*)guiInputs->getWidget("Servers");
        vector<string> names = list->getSelectedNames();
        if (names.size() == 1) {
            syphon.setApplicationName(names[0]);
            elements["Syphon"]->corner[0] = ofVec2f(0, 0);
            elements["Syphon"]->corner[1] = ofVec2f(syphon.getWidth(), 0);
            elements["Syphon"]->corner[2] = ofVec2f(syphon.getWidth(), syphon.getHeight());
            elements["Syphon"]->corner[3] = ofVec2f(0, syphon.getHeight());
            
            elements["Syphon"]->width = syphon.getWidth();
            elements["Syphon"]->height = syphon.getHeight();
        }
    }
    if (name == "Outputs") {
        guiOutputs->setVisible(e.getToggle()->getValue());
    }
    if (name == "Settings") {
        guiSettings->setVisible(e.getToggle()->getValue());
    }
    if (name == "Width") {
        int width = ((ofxUINumberDialer*)e.widget)->getValue();
        canvas.setWidth(width);
    }
    if (name == "Height") {
        int height = ((ofxUINumberDialer*)e.widget)->getValue();
        canvas.setHeight(height);
    }
    if (name == "Info") {
        guiInfo->setVisible(e.getToggle()->getValue());
    }
    if (name == "FullScreen") {
        ofSetFullscreen(e.getButton()->getValue());
    }
}

void testApp::syphonServerAnnounced(ofxSyphonServerDirectoryEventArgs &arg) {

    ofxUIDropDownList *list = (ofxUIDropDownList*)guiInputs->getWidget("Servers");
    
    for (vector<ofxSyphonServerDescription>::iterator it = arg.servers.begin(); it != arg.servers.end(); ++it) {
        list->addToggle(it->appName);
    }
}
