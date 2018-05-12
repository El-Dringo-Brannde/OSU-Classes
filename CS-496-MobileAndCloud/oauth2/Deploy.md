# Build & Deploy

1. ` npm run build `
2. Create a bucket in Google Cloud Platform
3. Upload folder to the GCP bucket
4. open up the cloud console and type: ` gsutil rsync -r gs://{BUCKET_NAME} ./{APP} `
5. Then change directory to the folder where the app was created
6. type ` gcloud app deploy ` to deploy app to the cloud