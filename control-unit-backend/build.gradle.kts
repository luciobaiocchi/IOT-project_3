plugins {
    id("java")
    application
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:5.10.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
    implementation("io.github.java-native:jssc:2.9.6")
    implementation("org.slf4j:slf4j-simple:2.0.9")
    implementation ("org.jfree:jfreechart:1.5.3")

    // Vert.x dependencies
    implementation ("io.vertx:vertx-core:4.2.6")
    implementation ("io.vertx:vertx-web:4.2.6")
    implementation ("io.vertx:vertx-web-client:4.2.6")
    implementation ("io.vertx:vertx-mqtt:4.2.6")

    // Logging dependencies
    implementation ("org.slf4j:slf4j-api:1.7.25")

    // JUnit dependencies
    testImplementation ("org.junit.jupiter:junit-jupiter-api:5.11.0")
    testImplementation ("org.junit.jupiter:junit-jupiter-params:5.11.0")
    testRuntimeOnly ("org.junit.jupiter:junit-jupiter-engine:5.11.0'")
}

application {
    mainClass.set("Main")
}


tasks.test {
    useJUnitPlatform()
}

// Configurazione del compilatore Java
tasks.compileJava {
    options.release.set(17) // Imposta la versione di Java su 17
}