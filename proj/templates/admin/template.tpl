<?php

	namespace Proj\Admin\Templates;

	use Base\Debugger;use Base\Templates;
	use Base\Instance;
	use Base\Templates\Versions as BaseVersions;
use Proj\DBObject;use Proj\Templates\Admin\Versions as AdminVersions;

	class Template extends Templates\Template {
		use Instance;

		private function __construct() {
			parent::__construct();

			$this->AddScript('jq', 'https://code.jquery.com/jquery-3.6.1.min.js');
			$this->AddVersionScript('base_common', '/base/template/js/common', BaseVersions\COMMON_JS);
			$this->AddVersionScript('admin_common', '/proj/templates/admin/js/common', AdminVersions\COMMON_JS);
			$this->AddVersionScript('admin_general', '/proj/templates/admin/js/general', AdminVersions\GENERAL_JS);

			$this->AddVersionStylesheet('main', DIR_REL_TPL . 'admin/css/main', AdminVersions\MAIN_CSS);
		}

		public static function ToVar(): string {
			Templates\Template::Start();
			self::Render();
			return Templates\Template::Read();
		}

		public static function Render(): void { ?><!doctype html>
			<html lang  = "ru"<?php Template::instance()->BrowseData(); ?>>
				<head>
					<meta charset = "UTF-8">
					<meta name = "viewport" content = "width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
					<meta http-equiv = "X-UA-Compatible" content = "ie=edge">
					<link type = "image/x-icon" href = "<?= DIR_REL_FILES_IMAGE; ?>favicon.ico" rel = "icon">
					<?php Template::$instance->BrowseHead(); ?>
				</head>
				<body>
					<?php self::RenderSections(); ?>
				</body>
			</html>
		<?php }

		private static function RenderSections(): void { ?>
			<header><?php Layout::instance()->header->Browse(); ?></header>
			<div>
				<menu><?php Layout::instance()->menu->Browse(); ?></menu>
				<main><?php Layout::instance()->main->Browse(); ?></main>
			</div>
			<footer><?php Layout::instance()->footer->Browse(); ?></footer>
			<script>
				<?php Layout::instance()->js_global->Browse(); ?>
				$(() => {
					Base.Common.GlobalParams.Set('request', '<?= \REQUEST; ?>');
					Base.Common.GlobalParams.Set('xhr', '<?= \XHR; ?>');
					getContent('admin');
					Base.Common.History.Initialization();
					Admin.Common.Layout.Initialization();
					Base.Common.Debugger.Initialization();
					Base.Common.Debugger.Append(<?= json_encode(Debugger::Get()); ?>);
				<?php Layout::instance()->js_loaded->Browse(); ?>
				});
			</script>
		<?php }

	}

	Template::init();