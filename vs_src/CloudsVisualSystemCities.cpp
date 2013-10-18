//
//  CloudsVisualSystemCities.cpp
//
//  Created by Patricio Gonzalez Vivo on 5/26/13.
//
//

#include "CloudsVisualSystemCities.h"

string CloudsVisualSystemCities::getSystemName()
{
	return "Cities";
}

void CloudsVisualSystemCities::makeBigCubesVbo( int _size, int _resolution )
{
	//create a huge vbo filled with cubes
	//
	size = _size;
    resolution = _resolution;
    blockSize = size/resolution;
	
	//make our base cube who's vertices and indices we'll use to populate our big cubesMesh
	ofVboMesh m;
	makeCubeMeshWithTexCoords( m, 1,2,1 );
	vector<ofVec3f>& cubeVertices = m.getVertices();
	vector<ofVec3f>& cubeNormals = m.getNormals();
	vector<ofIndexType>& cubeIndices = m.getIndices();

	//make a vbo full of cubes
	cubeMesh.clear();
	vector<ofVec3f>& vertices = cubeMesh.getVertices();
	vector<ofVec2f> facadeUV;
	ofIndexType firstIndex;
	ofVec3f offset( -resolution/2, 0, -resolution/2 );
	ofVec2f tc( 1./float(resolution-1), 1./float(resolution-1));
	for (int i=0; i<resolution; i++)
	{
		for (int j=0; j<resolution; j++)
		{
			//store our first cube index
			firstIndex = vertices.size();
			
			//add our vertices
			for (int k=0; k<cubeVertices.size(); k++)
			{
				//add our vertex and normal
				cubeMesh.addVertex( cubeVertices[k] + offset + ofVec3f(i, 0, j));
				cubeMesh.addNormal( cubeNormals[k] );
				
				//our texCoords are the same for each vertex in the cube
				cubeMesh.addTexCoord( ofVec2f(i - .5, j - .5) * tc );
				
				

			}
			
			//add our indices
			for (int k=0; k<cubeIndices.size(); k++) {
				cubeMesh.addIndex( cubeIndices[k] + firstIndex );
			}
		}
	}
	
	m.clear();
}

void CloudsVisualSystemCities::generateCube(float sizeX, float sizeY, float sizeZ)
{
    ofPushMatrix();
    
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    if(ofGetStyle().bFill) {
        GLfloat vertices[] = {
            +sizeX,-sizeY,+sizeZ, +sizeX,-sizeY,-sizeZ, +sizeX,+sizeY,-sizeZ, +sizeX,+sizeY,+sizeZ,
            +sizeX,+sizeY,+sizeZ, +sizeX,+sizeY,-sizeZ, -sizeX,+sizeY,-sizeZ, -sizeX,+sizeY,+sizeZ,
            +sizeX,+sizeY,+sizeZ, -sizeX,+sizeY,+sizeZ, -sizeX,-sizeY,+sizeZ, +sizeX,-sizeY,+sizeZ,
            -sizeX,-sizeY,+sizeZ, -sizeX,+sizeY,+sizeZ, -sizeX,+sizeY,-sizeZ, -sizeX,-sizeY,-sizeZ,
            -sizeX,-sizeY,+sizeZ, -sizeX,-sizeY,-sizeZ, +sizeX,-sizeY,-sizeZ, +sizeX,-sizeY,+sizeZ,
            -sizeX,-sizeY,-sizeZ, -sizeX,+sizeY,-sizeZ, +sizeX,+sizeY,-sizeZ, +sizeX,-sizeY,-sizeZ
        };
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        
        static GLfloat normals[] = {
            +1,0,0, +1,0,0, +1,0,0, +1,0,0,
            0,+1,0, 0,+1,0, 0,+1,0, 0,+1,0,
            0,0,-1, 0,0,-1, 0,0,-1, 0,0,-1,
            -1,0,0, -1,0,0, -1,0,0, -1,0,0,
            0,-1,0, 0,-1,0, 0,-1,0, 0,-1,0,
            0,0,+1, 0,0,+1, 0,0,+1, 0,0,+1
        };
        glNormalPointer(GL_FLOAT, 0, normals);
        
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        static GLfloat tex[] = {
            1,0, 0,0, 0,1, 1,1,
            1,1, 1,0, 0,0, 0,1,
            0,1, 1,1, 1,0, 0,0,
            0,0, 0,1, 1,1, 1,0,
            0,0, 0,1, 1,1, 1,0,
            0,0, 0,1, 1,1, 1,0
        };
        glTexCoordPointer(2, GL_FLOAT, 0, tex);
        
        GLubyte indices[] = {
            0,1,2, // right top left
            0,2,3, // right bottom right
            4,5,6, // bottom top right
            4,6,7, // bottom bottom left
            8,9,10, // back bottom right
            8,10,11, // back top left
            12,13,14, // left bottom right
            12,14,15, // left top left
            16,17,18, // ... etc
            16,18,19,
            20,21,22,
            20,22,23
        };
        glDrawElements(GL_TRIANGLES, 3 * 6 * 2, GL_UNSIGNED_BYTE, indices);
        
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    } else {
        GLfloat vertices[] = {
            +sizeX,+sizeY,+sizeZ,
            +sizeX,+sizeY,-sizeZ,
            +sizeX,-sizeY,+sizeZ,
            +sizeX,-sizeY,-sizeZ,
            -sizeX,+sizeY,+sizeZ,
            -sizeX,+sizeY,-sizeZ,
            -sizeX,-sizeY,+sizeZ,
            -sizeX,-sizeY,-sizeZ
        };
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        
        static float n = sqrtf(3);
        static GLfloat normals[] = {
            +n,+n,+n,
            +n,+n,-n,
            +n,-n,+n,
            +n,-n,-n,
            -n,+n,+n,
            -n,+n,-n,
            -n,-n,+n,
            -n,-n,-n
        };
        glNormalPointer(GL_FLOAT, 0, normals);
        
        static GLubyte indices[] = {
            0,1, 1,3, 3,2, 2,0,
            4,5, 5,7, 7,6, 6,4,
            0,4, 5,1, 7,3, 6,2
        };
        glDrawElements(GL_LINES, 4 * 2 * 3, GL_UNSIGNED_BYTE, indices);
    }
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
    ofPopMatrix();
}

void CloudsVisualSystemCities::selfSetup()
{
    size = 100;
    resolution = 1;
    blockSize = 1;

    grayscottLoops = 10;
    nPingPong = 0;
    diffU=0.25;
    diffV=0.04;
    k=0.047;
    f=0.2;
    
	
    //  Noise
    //
    noiseShader.load("", getVisualSystemDataPath()+"shaders/noise.fs");
    
    //  GrayScott
    //
    grayscottShader.load("", getVisualSystemDataPath()+"shaders/grayscott.fs");
    
    //  Mask
    //
    maskShader.load("", getVisualSystemDataPath()+"shaders/cMask.fs");
    
	//Overlay
	//
	bUseOverlay = false;
	overlayMap = NULL;
	string overlayPath = getVisualSystemDataPath() + "images/overlayImages/";
	
	ofDirectory dir;
	dir.listDir( overlayPath );
	for(int i = 0; i < dir.numFiles(); i++){
		overlayNames.push_back( dir.getName(i) );
		overlayImageMap[dir.getName(i)];
	}
	
	for (map<string, ofImage>::iterator it=overlayImageMap.begin(); it!=overlayImageMap.end(); it++)
	{
		it->second.loadImage( overlayPath + it->first );
	}
	
	
	
    //  Points
    //
    makeGrid(100, 10);
	
	//cubes shader
	cubesShader.load(getVisualSystemDataPath()+"shaders/city");
    
    //  Post
    //
    postShader.load("",getVisualSystemDataPath()+"shaders/postprocess.fs");
    ofLoadImage(postTexture, getVisualSystemDataPath()+"images/6.jpg");
}

void CloudsVisualSystemCities::selfBegin()
{
    
}

void CloudsVisualSystemCities::selfEnd()
{
    
}

void CloudsVisualSystemCities::selfSetupSystemGui()
{
    
    sysGui->addLabel("Noise");
    sysGui->addSlider("noise_zoom", 0.0, 100.0, &noiseZoom);
    sysGui->addSlider("noise_speed", 0.0, 5.0, &noiseSpeed);
    
    sysGui->addLabel("GrayScott");
    sysGui->addSlider("Feed", 0.0, 0.1, &grayscottFade);
    sysGui->addSlider("Loops", 1.0, 25, &grayscottLoops);
//    sysGui->addSlider("DiffV", 0.0, 1.0, &diffV);
//    sysGui->addSlider("DiffU", 0.0, 1.0, &diffU);
//    sysGui->addSlider("k", 0.0, 1.0, &k);
//    sysGui->addSlider("t", 0.0, 1.0, &f);
    
    sysGui->addToggle("enable", &bGrayscott);
    sysGui->addButton("clean", &bCleanGrayscott);
    
    sysGui->addLabel("Mask");
    sysGui->addSlider("maskSize", 1.0, 2.0, &maskSize);
    sysGui->addSlider("maskCurve", 0.0, 1.0, &maskCurve);
	
	sysGui->addSpacer();
	sysGui->addToggle("use overlay", &bUseOverlay);
	sysGui->addSpacer();
	sysGui->addLabel("over lays");
	sysGui->addRadio("overlay map", overlayNames);
}

void CloudsVisualSystemCities::selfGuiEvent(ofxUIEventArgs &e)
{
}

void CloudsVisualSystemCities::guiSystemEvent(ofxUIEventArgs &e)
{
	if(e.widget->getKind() == OFX_UI_WIDGET_TOGGLE && e.getToggle()->getValue())
	{
		string name = e.getName();
		for (map<string, ofImage>::iterator it=overlayImageMap.begin(); it!=overlayImageMap.end(); it++)
		{
			if(it->first == name)
			{
				overlayMap = &it->second;
				bUseOverlay = true;
				
				cout << bUseOverlay << " : " << overlayMap <<  endl;
			}
		}
		
	}
}

void CloudsVisualSystemCities::guiRenderEvent(ofxUIEventArgs &e)
{	
    string name = e.widget->getName();
    if (name == "Size" || name == "Resolution"){
        makeGrid(size, resolution);
    }
}

void CloudsVisualSystemCities::selfSetupRenderGui()
{
    rdrGui->addSlider("Size", 10, 200, &size);
    rdrGui->addSlider("Resolution", 1, 100, &resolution);
    rdrGui->addSlider("Height", 0, 100, &height);
    
    rdrGui->addLabel("Blocks");
    rdrGui->addSlider("Min_Dist", 0.0, 0.5, &blocksMinDist);
    rdrGui->addSlider("Min_Size", 0.0, 1.0, &blocksMinSize);
    rdrGui->addSlider("Blocks_Alpha", 0.0, 1.0, &blocksAlpha);
    
    rdrGui->addLabel("Post-Process");
    rdrGui->addSlider("Chroma_Distortion", -1.0, 1.0, &postChromaDist);
    rdrGui->addSlider("Grain_Distortion", 0.0, 1.0, &postGrainDist);
}

void CloudsVisualSystemCities::makeGrid(float _size, int _resolution)
{
    size = _size;
    resolution = _resolution;
    blockSize = size/resolution;

    //  Noise Texture
    //
    int textureSize = resolution*2;
    noiseFbo.allocate(textureSize,textureSize);
    noiseFbo.begin();
    ofClear(0);
    noiseFbo.end();
    
    //  Grayscott PingPong
    //
    for(int i = 0; i < 2; i++){
        grayscottFbo[i].allocate(textureSize, textureSize);
        grayscottFbo[i].begin();
        ofClear(0);
        grayscottFbo[i].end();
    }
    
    //  Mask FBO
    //
    maskFbo.allocate(textureSize, textureSize);
    maskFbo.begin();
    ofClear(0);
    maskFbo.end();
    
    //  Generate Blocks
    //
    cube = glGenLists(1);
    float cubeSize = blockSize*0.5;
    glNewList(cube, GL_COMPILE);
    generateCube(cubeSize, cubeSize, cubeSize);
    glEndList();
	
	makeBigCubesVbo( _size, resolution );
}

void CloudsVisualSystemCities::selfUpdate()
{
    ofPushStyle();
    
    ofSetColor(255);
    
    int texWidth = noiseFbo.getWidth();
    int texHeight = noiseFbo.getHeight();
    noiseFbo.begin();
    ofClear(0);
    noiseShader.begin();
    noiseShader.setUniform2f("resolution", texWidth,texHeight);
    noiseShader.setUniform1f("time", ofGetElapsedTimef()*noiseSpeed);
    noiseShader.setUniform1f("zoom", noiseZoom);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(texWidth, 0); glVertex3f(texWidth, 0, 0);
    glTexCoord2f(texWidth, texHeight); glVertex3f(texWidth, texHeight, 0);
    glTexCoord2f(0,texHeight);  glVertex3f(0,texHeight, 0);
    glEnd();
    noiseShader.end();
    noiseFbo.end();
    
    if(bGrayscott){
        if (bCleanGrayscott){
            for (int i = 0; i < 2; i++) {
                grayscottFbo[i].begin();
                ofClear(0);
                grayscottFbo[i].end();
            }
            bCleanGrayscott = false;
        }
        
        for (int i = 0; i < grayscottLoops; i++) {
            nPingPong = (nPingPong+1)%2;
            
            grayscottFbo[nPingPong%2].begin();
            grayscottShader.begin();
            grayscottShader.setUniformTexture("backbuffer", grayscottFbo[(nPingPong+1)%2], 1);
            grayscottShader.setUniformTexture("tex0", noiseFbo, 2);
            grayscottShader.setUniform1f("diffU", diffU);
            grayscottShader.setUniform1f("diffV", diffV);
            grayscottShader.setUniform1f("k", k);
            grayscottShader.setUniform1f("f", f);
            grayscottShader.setUniform1f("time", ofGetElapsedTimef());
            grayscottShader.setUniform1f("fade", grayscottFade);
            glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
            glTexCoord2f(texWidth, 0); glVertex3f(texWidth, 0, 0);
            glTexCoord2f(texWidth, texHeight); glVertex3f(texWidth, texHeight, 0);
            glTexCoord2f(0,texHeight);  glVertex3f(0,texHeight, 0);
            glEnd();
            grayscottShader.end();
            grayscottFbo[nPingPong%2].end();
        }
    }
    
    maskFbo.begin();
    ofClear(0);
    maskShader.begin();
    maskShader.setUniform2f("resolution", texWidth, texHeight);
    maskShader.setUniform1f("size", maskSize);
    maskShader.setUniform1f("curve",maskCurve);
    
    if(bGrayscott){
        grayscottFbo[nPingPong%2].draw(0, 0);
    } else {
        noiseFbo.draw(0, 0);
    }
    maskShader.end();
    maskFbo.end();
    
    ofPopStyle();
}

void CloudsVisualSystemCities::selfDraw()
{	
 //    ofPushMatrix();
//    
//    glEnable(GL_DEPTH_TEST);
//    ofTranslate(-size*0.5,-size*0.5);
//    ofFill();
//    
//    ofSetColor(255);
//    ofFloatPixels heightPixels;
//    maskFbo.getTextureReference().readToPixels(heightPixels);
//    
//    int jump = heightPixels.getWidth()/resolution;
//    for(int x = 0; x < resolution; x++){
//        for(int y = 0; y < resolution; y++){
//            
//            float value = heightPixels.getColor(x*jump,y*jump).b;
//            
//            ofPushMatrix();
//            ofTranslate(x*blockSize,y*blockSize, height*value*0.5*blockSize );
//            
//            if ( value > 0.0){
//                ofSetColor(255, MAX(blocksAlpha*255,55+value*200.0) );
//                ofScale((1.0 - blocksMinDist) - value * blocksMinSize,
//                        (1.0 - blocksMinDist) - value * blocksMinSize,
//                        height*value);
//                
//                //PATRICIO: seeing crashing here when called from CLOUDS thread
//                glCallList(cube);
//                
//            }
//            ofPopMatrix();
//        }
//    }
//    ofPopMatrix();
//
//    glDisable(GL_DEPTH_TEST);
	
	
	
	ofPushMatrix();
	ofRotate(90, 1, 0, 0);
	ofScale(blockSize,blockSize,-blockSize);
	
	cubesShader.begin();
	cubesShader.setUniformTexture("displacment", maskFbo.getTextureReference(), 0);
	cubesShader.setUniform2f( "displacmentDim", maskFbo.getWidth(), maskFbo.getHeight());
	
	if(bUseOverlay && overlayMap != NULL){
		cubesShader.setUniformTexture("overlayMap", overlayMap->getTextureReference(), 1);
		cubesShader.setUniform2f("overlayDim", overlayMap->getWidth(), overlayMap->getHeight());
	}
	cubesShader.setUniform1i("bUseOverlay", bUseOverlay );
	
	cubesShader.setUniform1f("blocksAlpha", blocksAlpha );
	cubesShader.setUniform1f("minHeight", .05 );
	cubesShader.setUniform1f("maxHeight", height / blockSize );
	cubesShader.setUniform1f("blockSize", blockSize );
	cubesShader.setUniform1f("blocksMinDist", blocksMinDist );
	cubesShader.setUniform1f("blocksMinSize", blocksMinSize );
	cubesShader.setUniform1f("shininess", 32. );//TODO: add a slider and variable for shininess

//	cubesShader.setUniform1f("lightColor", )
	
//	uniform vec3 lightColor;
//	uniform vec3 lightPos;
	
	ofEnableAlphaBlending();
	ofBlendMode( OF_BLENDMODE_SCREEN );
	
//	glClearDepth(1);
	
//	glDisable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	
//	glDepthFunc( GL_LESS ); // GL_LESS, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, and GL_ALWAYS
	cubeMesh.draw();
	
	glEnable( GL_DEPTH_TEST );
	glCullFace( GL_FRONT );
	cubeMesh.draw();
	
	cubesShader.end();
	
	ofPopMatrix();
	glDisable(GL_DEPTH_TEST);
	glDisable( GL_CULL_FACE );
}

void CloudsVisualSystemCities::selfPostDraw(){
    postShader.begin();
    postShader.setUniformTexture("tex1", postTexture, 1);
    postShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    postShader.setUniform2f("textureResolution", postTexture.getWidth(), postTexture.getHeight());
    postShader.setUniform1f("chromaDist", postChromaDist);
    postShader.setUniform1f("grainDist", postGrainDist);
    CloudsVisualSystem::selfPostDraw();
    postShader.end();
	
//	overlayMap.draw(0,0,400, 400);
}

void CloudsVisualSystemCities::billBoard()
{
    
}

void CloudsVisualSystemCities::selfSetupGuis()
{
    
}

void CloudsVisualSystemCities::selfAutoMode()
{
    
}

void CloudsVisualSystemCities::selfDrawBackground()
{
    
}

void CloudsVisualSystemCities::selfDrawDebug()
{
    
}

void CloudsVisualSystemCities::selfSceneTransformation()
{
    
}

void CloudsVisualSystemCities::selfExit()
{
    cubeMesh.clear();
}

void CloudsVisualSystemCities::selfKeyPressed(ofKeyEventArgs & args)
{
    if(args.key == 'l' || args.key == 'L')
	{
		cubesShader.load(getVisualSystemDataPath()+"shaders/city");
	}
}

void CloudsVisualSystemCities::selfKeyReleased(ofKeyEventArgs & args)
{
    
}

void CloudsVisualSystemCities::selfMouseDragged(ofMouseEventArgs& data)
{
    
}

void CloudsVisualSystemCities::selfMouseMoved(ofMouseEventArgs& data)
{
    
}

void CloudsVisualSystemCities::selfMousePressed(ofMouseEventArgs& data)
{
    
}

void CloudsVisualSystemCities::selfMouseReleased(ofMouseEventArgs& data)
{
    
}

void CloudsVisualSystemCities::selfSetupGui()
{
    
}
