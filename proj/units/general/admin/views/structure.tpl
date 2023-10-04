<?php

	namespace Proj\Admin\Templates\General;

	use Base\Templates\Buffering;

	abstract class Structure {

		public static function ToVar(array $data): string {
			Buffering::Start();
			self::Render($data);
			return Buffering::Read();
		}

		public static function Render(array $data): void { ?>
			<h1>Структура базы данных</h1>
			<div id = "structure"></div>
			<script>
				new Admin.General.Structure(<?= json_encode($data); ?>);
			</script>
		<?php }

	}