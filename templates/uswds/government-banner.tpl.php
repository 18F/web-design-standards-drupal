<div class="usa-accordion">
  <header class="usa-banner-header">
    <div class="usa-grid usa-banner-inner">
    <img src="<?php print $image_base ?>/favicons/favicon-57.png" alt="<?php print t('U.S. flag') ?>">
    <p><?php print t('An official website of the United States government') ?></p>
    <button class="usa-accordion-button usa-banner-button"
      aria-expanded="false" aria-controls="gov-banner">
      <span class="usa-banner-button-text"><?php print t('Here\'s how you know') ?></span>
    </button>
    </div>
  </header>
  <div class="usa-banner-content usa-grid usa-accordion-content" id="gov-banner">
    <div class="usa-banner-guidance-gov usa-width-one-half">
      <img class="usa-banner-icon usa-media_block-img" src="<?php print $image_base ?>/icon-dot-gov.svg" alt="<?php print t('Dot gov') ?>">
      <div class="usa-media_block-body">
        <p>
          <strong><?php print t('The .gov means it’s official.') ?></strong>
          <br>
          <?php print t('Federal government websites always use a .gov or .mil domain. Before sharing sensitive information online, make sure you’re on a .gov or .mil site by inspecting your browser’s address (or “location”) bar.') ?>
        </p>
      </div>
    </div>
    <div class="usa-banner-guidance-ssl usa-width-one-half">
      <img class="usa-banner-icon usa-media_block-img" src="<?php print $image_base ?>/icon-https.svg" alt="SSL">
      <div class="usa-media_block-body">
        <p><?php print t('This site is also protected by an SSL (Secure Sockets Layer) certificate that’s been signed by the U.S. government. The <strong>https://</strong> means all transmitted data is encrypted  — in other words, any information or browsing history that you provide is transmitted securely.') ?></p>
      </div>
    </div>
  </div>
</div>
