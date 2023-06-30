<?php

	namespace Proj\Admin\Templates\General;

	use Base\Templates\Template;

	abstract class Structure {

		public static function ToVar(array $data): string {
			Template::Start();
			self::Render($data);
			return Template::Read();
		}

		public static function Render(array $data): void { ?>
			<h1>Структура базы данных</h1>
			<div id = "structure"></div>
			<script>
				new Admin.General.Structure(<?= json_encode($data); ?>);
				DAD();

				function DAD() {
					let elem = document.getElementById('structure');

					elem.onmousedown = function(event) {
						let table = event.target.closest('.table');
						let drag = event.target.closest('.table > .drag');

						if (!table || !drag) return;

						table.style.zIndex = '1';

						document.onmousemove = function(event) {
							Move(event);
						};

						drag.onmouseup = function() {
							document.onmousemove = null;
							drag.onmouseup = null;
						};

						function Move(event) {
							let left = parseInt(table.style.left);
							if (isNaN(left)) left = 0;

							let top = parseInt(table.style.top);
							if (isNaN(top)) top = 0;
							table.style.left = `${left + event.movementX}px`;
							table.style.top = `${top + event.movementY}px`;
						}
					}

				}
			</script>
		<?php }

	}