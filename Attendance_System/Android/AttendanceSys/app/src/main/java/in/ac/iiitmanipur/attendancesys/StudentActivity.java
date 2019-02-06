package in.ac.iiitmanipur.attendancesys;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.firebase.ui.database.FirebaseRecyclerAdapter;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.zuowei.circleimageview.CircleImageView;

public class StudentActivity extends AppCompatActivity {

    private RecyclerView recyclerView;
    private DatabaseReference mDatabase;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_student);
        setTitle("Student");

        mDatabase = FirebaseDatabase.getInstance().getReference().child("ECE").child("SEM6").child("EC333");
        mDatabase.keepSynced(true);
        recyclerView = findViewById(R.id.my_recycler_view_student);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
    }

    @Override
    protected void onStart() {
        super.onStart();
        FirebaseRecyclerAdapter<studentgs, studentgsViewHolder> firebaseRecyclerAdapter = new FirebaseRecyclerAdapter<studentgs, studentgsViewHolder>
                (studentgs.class, R.layout.studentprofile,studentgsViewHolder.class,mDatabase){
            @Override
            protected void populateViewHolder(studentgsViewHolder viewHolder, studentgs model, int position){
                viewHolder.setName(model.getName());
                viewHolder.setId(String.valueOf(model.getId()));
                viewHolder.setImage(getApplicationContext(),model.getImage());
                viewHolder.setAttendance(model.getAttendance()+" %");
            }
        };
        recyclerView.setAdapter(firebaseRecyclerAdapter);
    }

    public static class studentgsViewHolder extends RecyclerView.ViewHolder
    {
        View mView;
        public studentgsViewHolder(View itemView)
        {
            super(itemView);
            mView = itemView;
        }
        public void setName(String name){
            TextView Title = (TextView)mView.findViewById(R.id.student_name);
            Title.setText(name);
        }

        public void setId(String id){
            TextView Title = (TextView)mView.findViewById(R.id.student_id);
            Title.setText(id);
        }

        public void setImage(Context ctx, String image){
            CircleImageView Title = (CircleImageView) mView.findViewById(R.id.image_view);
            Glide.with(ctx).load(image).into(Title);

        }

        public void setAttendance(String attendance){
            TextView Title = (TextView)mView.findViewById(R.id.student_attendance);
            Title.setText(attendance);
        }
    }
}
