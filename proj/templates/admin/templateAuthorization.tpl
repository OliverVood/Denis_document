<?php

	namespace Proj\Admin\Templates;

	use Base\Templates;
	use Base\Instance;
	use Base\Templates\Versions as BaseVersions;
	use Proj\Templates\Admin\Versions as AdminVersions;

	class TemplateAuthorization extends Templates\Template {
		use Instance;

		private function __construct() {
			parent::__construct();

			$this->AddScript('jq', 'https://code.jquery.com/jquery-3.6.1.min.js');
			$this->AddVersionScript('base_common', '/base/template/js/common', BaseVersions\COMMON_JS);
			$this->AddVersionScript('admin_users', '/proj/templates/admin/js/users', AdminVersions\USERS_JS);

			$this->AddVersionStylesheet('main', DIR_REL_TPL . 'admin/css/authorization', AdminVersions\AUTHORIZATION_CSS);
		}

		public static function ToVar(): string {
			Templates\Template::Start();
			self::Render();
			return Templates\Template::Read();
		}

		public static function Render(): void { ?><!doctype html>
			<html lang  = "ru"<?php TemplateAuthorization::instance()->BrowseData(); ?>>
				<head>
					<meta charset = "UTF-8">
					<meta name = "viewport" content = "width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
					<meta http-equiv = "X-UA-Compatible" content = "ie=edge">
					<link type = "image/x-icon" href = "<?= DIR_REL_FILES_IMAGE; ?>favicon.ico" rel = "icon">
					<title>Document</title>
					<?php
						TemplateAuthorization::$instance->BrowseHead();
					?>
				</head>
				<body>
					<?php self::RenderSections(); ?>
					<script>
						$(function() {
							Base.Common.GlobalParams.Set('request', '<?= \REQUEST; ?>');
							Base.Common.GlobalParams.Set('xhr', '<?= \XHR; ?>');
						});
					</script>
				</body>
			</html>
		<?php }

		private static function RenderSections(): void { ?>
			<header><?php LayoutAuthorization::instance()->header->Browse(); ?></header>
			<main><?php LayoutAuthorization::instance()->main->Browse(); ?></main>
			<footer><?php LayoutAuthorization::instance()->footer->Browse(); ?></footer>
		<?php }

	}

	TemplateAuthorization::init();