package il2cpp.typefaces;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.os.Handler;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.CompoundButton;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.ScrollView;
import android.widget.TextView;
import il2cpp.Utils;
import il2cpp.typefaces.WeaveTitle;
import java.util.ArrayList;
import java.util.prefs.Preferences;

class ColorList {
    public static int get_colorWhite() {
		return Color.parseColor("#91000000");
    }

    public static int get_colorLeft() {
        return Color.parseColor("#91000000");
    }

    public static int get_colorBlue() {
        return Color.parseColor("#91000000");
    }

    public static int get_colorBlack() {
        return Color.parseColor("#91000000");
    }

    public static int get_colorGray() {
        return Color.parseColor("#91000000");
    }

    public static int get_colorHeader() {
        return Color.parseColor("#91000000");
	}

	public static int colorMain () {
		return Color.parseColor("#101010");
	}

	public static int colorHeader () {
		return Color.parseColor("#9E000000");
	}

	public static int colorBody () {
		return Color.parseColor("#141414");
	}

	public static int colorGrayLight () {
		return Color.parseColor("#462c50");
	}

	public static int colorOrange () {
		return Color.parseColor("#CE04F2");
	}

	public static int colorRad() {
		return Color.parseColor("#ff0000");
	}
	public static int colorBLACKPON() {
		return Color.parseColor("#000000");
	}
	public static int colorBlue() {
		return Color.parseColor("#001aff");	
	}
	public static int colorGreen() {
		return Color.parseColor("#04ff00");	
	}

}

public class Menu
{
	

	
	
	protected int WIDTH,HEIGHT;
    
	public Typeface google(Context yes) {return Typeface.createFromAsset(yes.getAssets(), "Font.ttf");}
	
	protected Context context;
	protected FrameLayout _parentBox;
	protected LinearLayout __page;
	protected ScrollView __scroll;
	
	public ArrayList<PageButton> _pagebuttons = new ArrayList<>();
	public ArrayList<ComponentBlock> blocks = new ArrayList<>();
	public ArrayList<LinearLayout> __pages = new ArrayList<>();
	
	public ImageView _icon;
	public TextView __pagetitle;
	public ImageView __pagesrc;
	public boolean _isShow = false;
	
	public LinearLayout menulayout,n1,y1,y2,pgs,scrl,h1;
	public TextView text,close;
    
 
	protected WindowManager wmManager;
	protected WindowManager.LayoutParams wmParams;
	
	protected void init(Context context) {
		
		this.context = context;
		
		_parentBox = new FrameLayout(context);

		_parentBox.setOnTouchListener(handleMotionTouch);
		wmManager = ((Activity)context).getWindowManager();
		int aditionalFlags=0;
		if (Build.VERSION.SDK_INT >= 11)
			aditionalFlags = WindowManager.LayoutParams.FLAG_SPLIT_TOUCH;
		if (Build.VERSION.SDK_INT >=  3)
			aditionalFlags = aditionalFlags | WindowManager.LayoutParams.FLAG_ALT_FOCUSABLE_IM;
		wmParams = new WindowManager.LayoutParams(
			WindowManager.LayoutParams.WRAP_CONTENT,
			WindowManager.LayoutParams.WRAP_CONTENT,
			0,//initialX
			0,//initialy
			WindowManager.LayoutParams.TYPE_APPLICATION,
			WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE |
			WindowManager.LayoutParams.FLAG_LAYOUT_IN_OVERSCAN |
			aditionalFlags,
			PixelFormat.TRANSPARENT
		);
		wmParams.gravity = Gravity.CENTER;//
	}
	
	public int dpi(float dp) {
		float scale = context.getResources().getDisplayMetrics().density;
		return (int) (dp * scale + 0.5f);
	}
	
	public void showMenu() {
		_isShow = true;
		_parentBox.removeAllViews();
		_parentBox.addView(menulayout);
	}

	public void hideMenu() {
		_isShow = false;
		new Handler().postDelayed(new Runnable() {
			public void run() {
				_parentBox.removeAllViews();
				_parentBox.addView(_icon, dpi(50), dpi(50));
				Utils.anim(_icon, 0);
			}
		}, 0);
	}
	
	
		public int newBlock(int pageid, String[] names) {
        final int blockid = blocks.size();

        LinearLayout blockline = new LinearLayout(context);
        blockline.setOrientation(LinearLayout.HORIZONTAL);

        for (int i = 0; i < names.length; i++) {
            String name = names[i];
            ComponentBlock block = new ComponentBlock(context, name);
            blocks.add(block);

            if (names.length > 1) {
                if ((i != 0)) {
                    LinearLayout expand = new LinearLayout(context);
                    blockline.addView(expand, dpi(7), -1);
                }
            }
            blockline.addView(block, new LinearLayout.LayoutParams(-1, -1, 1));

        }
        __pages.get(pageid).addView(blockline, -1, -2);
        return blockid;
	} 
	
	public void newPage(final String nm, final String src) {
		LinearLayout _page = new LinearLayout(context);
		PageButton _butt = new PageButton(context, nm, src);
		final int pageid = __pages.size();
		__page.setOrientation(LinearLayout.VERTICAL);
		_page.setOrientation(LinearLayout.VERTICAL);
		__page.addView(_page, -1, -1);
		_page.setVisibility(View.GONE);
		__pages.add(_page);
		_butt.callback = new PageButton.Callback() {
			public void onClick() {
				__pagetitle.setText(nm);
				Utils.SetAssets(context, __pagesrc, src);
				showPage(pageid);
			}
		};
		
		_pagebuttons.add(_butt);
		pgs.addView(_butt);
	}
	
	public void newTitle(int boxid, String text) {
		WeaveTitle titlenew = new WeaveTitle(context, text);
		__pages.get(boxid).addView(titlenew, -1, -2);
	}
	
	
	public ArrayList<Object> views = new ArrayList<>();
	
	public void showPage(final int id) {
		for (PageButton pg: _pagebuttons) {
			pg.hide();
		}
		for (LinearLayout layout: __pages) {
			layout.setVisibility(View.GONE);
		}
		__pages.get(id).setVisibility(View.VISIBLE);
		_pagebuttons.get(id).show();
		Utils.anim(__pages.get(id), 50);
	}
    
    
	public Menu(Context context)
	{
		init(context);
		
		_icon = new ImageView(context);
		Utils.SetAssets(context, _icon, "icon.png");
		
		menulayout = new LinearLayout(context);
		{
			menulayout.setOrientation(LinearLayout.HORIZONTAL);
			menulayout.setPadding(15,15,15,15);
			menulayout.setGravity(51);

			GradientDrawable design = new GradientDrawable();
			design.setColor(-15461358);
			design.setCornerRadius(10f);
			design.setStroke(0, -16777216);
			menulayout.setBackgroundDrawable(design);

			LayoutParams lp = new LayoutParams(dpi(408), dpi(235), 0);
			lp.leftMargin   = 0;
			lp.topMargin    = 0;
			lp.rightMargin  = 0;
			lp.bottomMargin = 0;
			menulayout.setLayoutParams(lp);
		}

		n1 = new LinearLayout(context);
		{
			n1.setOrientation(LinearLayout.VERTICAL);
			n1.setPadding(0,0,0,0);
			n1.setGravity(51);

			GradientDrawable design = new GradientDrawable();
			design.setColor(0);
			design.setCornerRadius(10f);
			design.setStroke(0, -16777216);
			n1.setBackgroundDrawable(design);

			LayoutParams lp = new LayoutParams(dpi(140), -1, 0);
			lp.leftMargin   = 0;
			lp.topMargin    = 0;
			lp.rightMargin  = 15;
			lp.bottomMargin = 0;
			n1.setLayoutParams(lp);
		}
		menulayout.addView(n1);
		
		y1 = new LinearLayout(context);
		{
			y1.setOrientation(LinearLayout.VERTICAL);
			y1.setPadding(15,7,15,7);
			y1.setGravity(17 | Gravity.TOP);

			GradientDrawable design = new GradientDrawable();
			design.setColor(-14737633);
			design.setCornerRadius(10f);
			design.setStroke(0, -16777216);
			y1.setBackgroundDrawable(design);

			LayoutParams lp = new LayoutParams(-1, dpi(50), 0);
			lp.leftMargin   = 0;
			lp.topMargin    = 0;
			lp.rightMargin  = 0;
			lp.bottomMargin = 15;
			y1.setLayoutParams(lp);
		}
		n1.addView(y1);
		
		y2 = new LinearLayout(context);
		{
			y2.setOrientation(LinearLayout.VERTICAL);
			y2.setPadding(15,15,15,15);
			y2.setGravity(17 | Gravity.TOP);

			GradientDrawable design = new GradientDrawable();
			design.setColor(-14737633);
			design.setCornerRadius(10f);
			design.setStroke(0, -16777216);
			y2.setBackgroundDrawable(design);

			LayoutParams lp = new LayoutParams(-1, -1, 0);
			lp.leftMargin   = 0;
			lp.topMargin    = 0;
			lp.rightMargin  = 0;
			lp.bottomMargin = 0;
			y2.setLayoutParams(lp);
		}
		n1.addView(y2);
		
		pgs = new LinearLayout(context);
		{
			pgs.setOrientation(LinearLayout.VERTICAL);
			pgs.setPadding(0,0,0,0);
			pgs.setGravity(51);

			GradientDrawable design = new GradientDrawable();
			design.setColor(0);
			design.setCornerRadius(10f);
			design.setStroke(0, -16777216);
			pgs.setBackgroundDrawable(design);

			LayoutParams lp = new LayoutParams(-1, -1, 1);
			lp.leftMargin   = 0;
			lp.topMargin    = 0;
			lp.rightMargin  = 0;
			lp.bottomMargin = 0;
			pgs.setLayoutParams(lp);
		}
		y2.addView(pgs);
		
		scrl = new LinearLayout(context);
		{
			scrl.setOrientation(LinearLayout.VERTICAL);
			scrl.setPadding(15,15,15,15);
			scrl.setGravity(17 | Gravity.TOP);

			GradientDrawable design = new GradientDrawable();
			design.setColor(-14737633);
			design.setCornerRadius(10f);
			design.setStroke(0, -16777216);
			scrl.setBackgroundDrawable(design);

			LayoutParams lp = new LayoutParams(-1, -1, 0);
			lp.leftMargin   = 0;
			lp.topMargin    = 0;
			lp.rightMargin  = 0;
			lp.bottomMargin = 0;
			scrl.setLayoutParams(lp);
		}
		menulayout.addView(scrl);

		text = new TextView(context);
		{
			text.setText("JUMP-SOFT");
			text.setPadding(0, 0, 0, 0);
			text.setGravity(Gravity.CENTER);

			GradientDrawable design = new GradientDrawable();
			design.setColor(0);
			design.setCornerRadius(10f);
			design.setStroke(0, 0);
			text.setBackgroundDrawable(design);

			LayoutParams lp = new LayoutParams(-1, -1, 1);
			lp.leftMargin   = 0;
			lp.topMargin    = 0;
			lp.rightMargin  = 0;
			lp.bottomMargin = 0;
			text.setLayoutParams(lp);
			text.setTextColor(-1);
			text.setTextSize(10.0f);
			text.setTypeface(Utils.font(context));
		}
		y1.addView(text);
        
        h1 = new LinearLayout(context);
        {
            h1.setOrientation(LinearLayout.HORIZONTAL);
            h1.setPadding(0,0,0,0);
            h1.setGravity(17);

            GradientDrawable design = new GradientDrawable();
            design.setColor(-15461358);
            design.setCornerRadius(10f);
            design.setStroke(0, -16777216);
            h1.setBackgroundDrawable(design);

            LayoutParams lp = new LayoutParams(-1, dpi(25), 0);
            lp.leftMargin   = 0;
            lp.topMargin    = 0;
            lp.rightMargin  = 0;
            lp.bottomMargin = 0;
            h1.setLayoutParams(lp);
        }
		y1.addView(h1);
        
        close = new TextView(context);
        {
            close.setText("× Закрыть");
            close.setPadding(0, 0, 0, 0);
            close.setGravity(Gravity.CENTER);

            GradientDrawable design = new GradientDrawable();
            design.setColor(-13421773);
            design.setCornerRadius(10f);
            design.setStroke(0, 0);
            close.setBackgroundDrawable(design);

            LayoutParams lp = new LayoutParams(-1, dpi(21), 0);
            lp.leftMargin   = 0;
            lp.topMargin    = 0;
            lp.rightMargin  = 0;
            lp.bottomMargin = 0;
            close.setLayoutParams(lp);
            close.setTextColor(-1);
            close.setTextSize(10.0f);
            close.setTypeface(Utils.font(context));
        }
		y2.addView(close);
        
		TextView game = new TextView(context);
        {
            game.setText("BLACK RUSSIA");
            game.setPadding(0, 0, 0, 0);
            game.setGravity(Gravity.CENTER);

            GradientDrawable design = new GradientDrawable();
            design.setColor(0);
            design.setCornerRadius(10f);
            design.setStroke(0, 0);
            game.setBackgroundDrawable(design);

            LayoutParams lp = new LayoutParams(-1, -1, 0);
            lp.leftMargin   = 0;
            lp.topMargin    = 0;
            lp.rightMargin  = 0;
            lp.bottomMargin = 0;
            game.setLayoutParams(lp);
            game.setTextColor(Color.rgb(60,60,60));
            game.setTextSize(15.0f);
            game.setTypeface(Utils.font(context));
        }
		h1.addView(game);
        
        
        
        
        
		
		
		
		
TextView _pagetitle = new TextView(context);

ImageView _pagesrc = new ImageView(context);
		
		__pagetitle = _pagetitle;
		__pagesrc = _pagesrc;
		
		close.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				hideMenu();
			}
		});
		
		__scroll = new ScrollView(context);
		__scroll.setFillViewport(true);
		
		__page = new LinearLayout(context);
		__page.setOrientation(LinearLayout.VERTICAL);
		
		__scroll.addView(__page, -1, -1);
		scrl.addView(__scroll, -1, -1);
       
        //__scroll.addView(__page2, -1, -1);
		
		hideMenu();
		wmManager.addView(_parentBox, wmParams);
	}
	
	View.OnTouchListener handleMotionTouch = new View.OnTouchListener()
	{
		private float initX;          
		private float initY;
		private float touchX;
		private float touchY;

		double clock=0;
		
		@Override
		public boolean onTouch(View vw, MotionEvent ev)
		{

			switch (ev.getAction())
			{
				case MotionEvent.ACTION_DOWN:

					initX = wmParams.x;
					initY = wmParams.y;
					touchX = ev.getRawX();
					touchY = ev.getRawY();
					clock = System.currentTimeMillis();
					break;

				case MotionEvent.ACTION_MOVE:
					wmParams.x = (int)initX + (int)(ev.getRawX() - touchX);

					wmParams.y = (int)initY + (int)(ev.getRawY() - touchY);


					wmManager.updateViewLayout(vw, wmParams);
					break;

				case MotionEvent.ACTION_UP:
					if (!_isShow && (System.currentTimeMillis() < (clock + 200)))
					{
						showMenu();
					}
					break;
			}
			return true;
		}
	};
}
