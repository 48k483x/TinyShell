#!/bin/bash

# Create the COMMITS.md file if it does not exist
if [ ! -f COMMITS.md ]; then
    touch COMMITS.md
fi

# Loop 100 times
for i in {1..99}
do
   echo "a" >> COMMITS.md                       # Append "a" to the file
   git add COMMITS.md                           # Stage the file for commit
   git commit -m "🎉✅ Finished implementing feature updates and optimizations 🚀"  # Commit with the message
   git push # origin main                         # Push the commit to the remote repository
done

# Clean up the repository after finishing the loop
   rm -rf COMMITS.md
   git add COMMITS.md
   git commit -m "🎉✅ Finished implementing feature updates and optimizations 🚀"
   git push # origin main