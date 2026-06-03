package il2cpp.typefaces;

import android.content.Context;
import android.graphics.drawable.GradientDrawable;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;
import il2cpp.Utils;
import android.widget.ImageView;
import android.graphics.Color;

public class PageButton extends LinearLayout {
	Context context;
	
	public static interface Callback {
		public void onClick();
	}
	public Callback callback;
	View __isopen;
	
	public int dpi(float dp) {
		float scale = context.getResources().getDisplayMetrics().density;
		return (int) (dp * scale + 0.5f);
	}
	
	
TextView _pagetitle;
ImageView _pagesrc;

	public void show() {

		_pagetitle.setTextColor(Color.parseColor("#FFFFFF"));
		_pagetitle.setGravity(17);

		__isopen.setVisibility(View.VISIBLE);

		{
			this.setOrientation(0);
			this.setPadding(0,0,0,0);
			this.setGravity(17);

			GradientDrawable design = new GradientDrawable();
			design.setColor(-51401);
			design.setCornerRadii(new float[] { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f });
			design.setStroke(0, -16777216);
			this.setBackgroundDrawable(design);

			LayoutParams lp = new LayoutParams(-1, dpi(21), 0);
			lp.leftMargin   = 0;
			lp.topMargin    = 0;
			lp.rightMargin  = 0;
			lp.bottomMargin = 15;
			this.setLayoutParams(lp);
		}


	}

	public void hide() {

		_pagetitle.setTextColor(Color.WHITE);
		_pagetitle.setGravity(17);

		__isopen.setVisibility(View.GONE);

		{
			this.setOrientation(0);
			this.setPadding(0,0,0,0);
			this.setGravity(17);

			GradientDrawable design = new GradientDrawable();
			design.setColor(-13421773);
			design.setCornerRadii(new float[] { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f });
			design.setStroke(0, -16777216);
			this.setBackgroundDrawable(design);

			LayoutParams lp = new LayoutParams(-1, dpi(21), 0);
			lp.leftMargin   = 0;
			lp.topMargin    = 0;
			lp.rightMargin  = 0;
			lp.bottomMargin = 15;
			this.setLayoutParams(lp);
		}


	}
	
	public void anim() {
		Utils.anim(this, 0);
	}
	
	public PageButton(Context context, String __text, String __src) {
		super(context);
		this.context = context;
		
		
		
				{
					this.setOrientation(0);
					this.setPadding(0,0,0,0);
					this.setGravity(17);
					
					GradientDrawable design = new GradientDrawable();
					design.setColor(-13421773);
					design.setCornerRadii(new float[] { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f });
                    design.setStroke(0, -16777216);
					this.setBackgroundDrawable(design);
					
					LayoutParams lp = new LayoutParams(-1, dpi(21), 0);
					lp.leftMargin   = 0;
					lp.topMargin    = 0;
					lp.rightMargin  = 0;
					lp.bottomMargin = 15;
					this.setLayoutParams(lp);
				}
                
        _pagesrc = new ImageView(context);
        {
            _pagesrc.setPadding(5, 5, 5, 5);
            _pagesrc.setColorFilter(-1);

            GradientDrawable design = new GradientDrawable();
            design.setColor(0);
            design.setCornerRadii(new float[] { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
            design.setStroke(0, -16776961);
            _pagesrc.setBackgroundDrawable(design);

            LayoutParams lp = new LayoutParams(Utils.dp(context, 15), Utils.dp(context, 15), 0);
            lp.leftMargin   = 0;
            lp.topMargin    = 0;
            lp.rightMargin  = 0;
            lp.bottomMargin = 0;
            _pagesrc.setLayoutParams(lp);

            Utils.SetAssets(context, _pagesrc, "icon.png");
        }
		this.addView(_pagesrc);

		_pagetitle = new TextView(context);
				{
					_pagetitle.setText("TextView");
					_pagetitle.setPadding(5, 5, 5, 5);
					_pagetitle.setGravity(17);
					
					GradientDrawable design = new GradientDrawable();
					design.setColor(0);
					design.setCornerRadii(new float[] { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
					design.setStroke(1, 0);
					_pagetitle.setBackgroundDrawable(design);
					
					LayoutParams lp = new LayoutParams(-2, -2, 0);
					lp.leftMargin   = 0;
					lp.topMargin    = 0;
					lp.rightMargin  = 0;
					lp.bottomMargin = 0;
					_pagetitle.setLayoutParams(lp);
					_pagetitle.setTextColor(-1);
					_pagetitle.setTextSize(10.0f);
					_pagetitle.setTypeface(Utils.font(context));
				}
this.addView(_pagetitle);
LinearLayout _isopen = new LinearLayout(context);

		
		__isopen = _isopen;
		
		this.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				anim();
				if (callback != null) callback.onClick();
			}
		});
		_pagetitle.setText(__text);
		Utils.SetAssets(context, _pagesrc, __src);
	}
}
