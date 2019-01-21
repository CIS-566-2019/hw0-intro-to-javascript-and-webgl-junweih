import {vec3, vec4} from 'gl-matrix';
import Drawable from '../rendering/gl/Drawable';
import {gl} from '../globals';

class Cube extends Drawable {
    indices: Uint32Array;
    positions: Float32Array;
    normals: Float32Array;
    center: vec4;

    constructor(center: vec3) {
        super();
        this.center = vec4.fromValues(center[0], center[1], center[2], 1);
    }

    create() {
        const x = 3;
        const y = 2;
        const z = 1;
        this.indices =  new Uint32Array ([
            // front face z+1
            0, 1, 2,
            0, 2, 3,

            //back face z-1
            4, 5, 6,
            4, 6, 7,

            //right face x+1
            8, 9, 10,
            8, 10, 11,

            //left face x-1
            12, 13, 14,
            12, 14, 15,

            //top face y+1
            16, 17, 18,
            16, 18, 19,

            //bot face y-1
            20, 21, 22,
            20, 22, 23
        ]);

        this.normals = new Float32Array([
            // Front Face
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 0, 1, 0,

           // Right Face
            1, 0, 0, 0,
            1, 0, 0, 0,
            1, 0, 0, 0,
            1, 0, 0, 0,

           // Left Face
           -1, 0, 0, 0,
           -1, 0, 0, 0,
           -1, 0, 0, 0,
           -1, 0, 0, 0,

           // Back Face
           0, 0, -1, 0,
           0, 0, -1, 0,
           0, 0, -1, 0,
           0, 0, -1, 0,

           // Top Face
           0, 1, 0, 0,
           0, 1, 0, 0,
           0, 1, 0, 0,
           0, 1, 0, 0,

           // Bottom Face
           0, -1, 0, 0,
           0, -1, 0, 0,
           0, -1, 0, 0,
           0, -1, 0, 0]);

        this.positions = new Float32Array([ 
            // Front Face
            0.5,  0.5,  0.5, 1.0, 
            0.5, -0.5,  0.5, 1.0, 
           -0.5, -0.5,  0.5, 1.0, 
           -0.5,  0.5,  0.5, 1.0, 

           // Right Face
            0.5,  0.5, -0.5, 1.0, 
            0.5, -0.5, -0.5, 1.0, 
            0.5, -0.5,  0.5, 1.0, 
            0.5,  0.5,  0.5, 1.0, 

           // Left Face
           -0.5,  0.5,  0.5, 1.0, 
           -0.5, -0.5,  0.5, 1.0, 
           -0.5, -0.5, -0.5, 1.0, 
           -0.5,  0.5, -0.5, 1.0, 

           // Back Face
           -0.5,  0.5, -0.5, 1.0, 
           -0.5, -0.5, -0.5, 1.0, 
            0.5, -0.5, -0.5, 1.0, 
            0.5,  0.5, -0.5, 1.0, 

            // Top Face
            0.5,  0.5, -0.5, 1.0, 
            0.5,  0.5,  0.5, 1.0, 
           -0.5,  0.5,  0.5, 1.0, 
           -0.5,  0.5, -0.5, 1.0, 

            // Bottom Face
            0.5, -0.5,  0.5, 1.0, 
            0.5, -0.5, -0.5, 1.0, 
           -0.5, -0.5, -0.5, 1.0, 
           -0.5, -0.5,  0.5, 1.0  
           ]);

        this.generateIdx();
        this.generateNor();
        this.generatePos();

        this.count = this.indices.length;
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.bufIdx);
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this.indices, gl.STATIC_DRAW);

        gl.bindBuffer(gl.ARRAY_BUFFER, this.bufNor);
        gl.bufferData(gl.ARRAY_BUFFER, this.normals, gl.STATIC_DRAW);

        gl.bindBuffer(gl.ARRAY_BUFFER, this.bufPos);
        gl.bufferData(gl.ARRAY_BUFFER, this.positions, gl.STATIC_DRAW);

        console.log('create cube');
    }
}

export default Cube;