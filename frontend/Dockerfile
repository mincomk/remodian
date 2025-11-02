FROM node:22-slim AS build
WORKDIR /app
COPY package*.json ./
RUN npm i -D
COPY . .
RUN npm run build

FROM nginx:alpine
COPY --from=build /app/dist /usr/share/nginx/html
