package in.ac.iiitmanipur.attendancesys;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.support.constraint.solver.widgets.Snapshot;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.firebase.client.Firebase;
import com.firebase.ui.database.FirebaseRecyclerAdapter;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.ArrayList;

public class SubjectActivity extends AppCompatActivity {

    private RecyclerView recyclerView;
    private DatabaseReference mDatabase;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_subject);
        setTitle("Subject");

        mDatabase = FirebaseDatabase.getInstance().getReference().child("ECE").child("SEM6").child("Subject");
        mDatabase.keepSynced(true);
        recyclerView = findViewById(R.id.my_recycler_view);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
    }

    @Override
    protected void onStart() {
        super.onStart();
        FirebaseRecyclerAdapter<blog, blogViewHolder> firebaseRecyclerAdapter = new FirebaseRecyclerAdapter<blog, blogViewHolder>
                (blog.class, R.layout.my_text_view,blogViewHolder.class,mDatabase){
            @Override
            protected void populateViewHolder(blogViewHolder viewHolder, blog model, int position){
                viewHolder.setTitle(model.getTitle());

                //final String user_id=getRef(position).getKey();
                //here mView provides the view for  a particular user
                //through this we are sending the activity to the selected user profile
                viewHolder.mView.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Intent StudentIntent = new Intent(SubjectActivity.this,StudentActivity.class);
                        //StudentIntent.putExtra("user_id",user_id);
                        startActivity(StudentIntent);
                    }
                });


            }
        };
        recyclerView.setAdapter(firebaseRecyclerAdapter);
    }

    public static class blogViewHolder extends RecyclerView.ViewHolder{
        View mView;
        public blogViewHolder(View itemView){
            super(itemView);
            mView = itemView;
        }
        public void setTitle(String title){
            TextView Title = (TextView)mView.findViewById(R.id.subj_name);
            Title.setText(title);
        }
    }
}
