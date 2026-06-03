package il2cpp;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.widget.LinearLayout;

public class ActivityMain extends Activity  
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
	
		System.loadLibrary("gvraudio");
		
		KEY.Start(this);
		
		LinearLayout lt = new LinearLayout(this);
        lt.setLayoutParams(new LinearLayout.LayoutParams(30,30));
        lt.setBackgroundColor(Color.parseColor("#940AD5"));
		setContentView(lt);
    }
}
