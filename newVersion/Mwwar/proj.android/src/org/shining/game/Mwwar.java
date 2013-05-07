/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.shining.game;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.KeyEvent;
import android.widget.Toast;

public class Mwwar extends Cocos2dxActivity{

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
	}
	public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// TestCpp should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		Toast.makeText(Mwwar.this, "Home键"+ keyCode,Toast.LENGTH_SHORT).show();
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			new AlertDialog.Builder(this) 
			.setTitle("确认")
			.setMessage("确定退出吗？")
			.setPositiveButton("是", new DialogInterface.OnClickListener() {  
                public void onClick(DialogInterface dialog, int which) {  
                	Mwwar.this.finish(); 
                }  
             })
			.setNegativeButton("否", null)
			.show();
		}else if(keyCode == KeyEvent.KEYCODE_HOME) {
			Toast.makeText(Mwwar.this, "Home键",Toast.LENGTH_SHORT).show();
		}
		return super.onKeyDown(keyCode, event);
	}
    static {
         System.loadLibrary("game");
    }
    @Override
    protected void onSaveInstanceState(Bundle outState){
         outState.putString("lastPath", "/sdcard/android/game/test");
    }


    @Override 
    public void onRestoreInstanceState(Bundle savedInstanceState) { 
         super.onRestoreInstanceState(savedInstanceState);

         String cwjString = savedInstanceState.getString("lastPath"); 
    }
}
